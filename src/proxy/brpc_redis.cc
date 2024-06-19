#include "brpc_redis.h"
#include <bthread/bthread.h>
#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include "redis_task.h"

namespace pikiwidb {

void* thread_entry(void* arg) {
  auto func = static_cast<std::function<void()>*>(arg);
  (*func)();
  delete func;  // 释放资源
  return nullptr;
}

void BrpcRedis::PushRedisTask(const std::shared_ptr<RedisTask>& task) {
  std::lock_guard<std::mutex> lock(lock_);
  tasks_.push_back(task);
}

void BrpcRedis::Commit() {
  brpc::RedisRequest request;
  brpc::RedisResponse response;
  brpc::Controller cntl;
  std::vector<std::shared_ptr<RedisTask>> task_batch;
  size_t batch_size = std::min(tasks_.size(), batch_size_);

  {
    std::lock_guard<std::mutex> lock(lock_);
    task_batch.assign(tasks_.begin(), tasks_.begin() + batch_size);
    tasks_.erase(tasks_.begin(), tasks_.begin() + batch_size);
  }

  for (auto& task : task_batch) {
    // TODO(hky): modify the brpc request
  }

  bthread_t bthread;

  // use callback to deal with a batch
  auto callback = new std::function<void()>([&]() {
    channel_.CallMethod(nullptr, &cntl, &request, &response, nullptr);
    for (size_t i = 0; i < task_batch.size(); i++) {
      SetResponse(response, task_batch[i], i);
    }
  });

  bthread_start_background(&bthread, nullptr, thread_entry, callback);
}
}  // namespace pikiwidb