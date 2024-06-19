#pragma once
#include <brpc/channel.h>
#include <brpc/redis.h>
#include <cstddef>
#include <memory>
#include <mutex>
#include <queue>
#include <vector>
#include "brpc/redis_reply.h"
#include "redis.h"
#include "redis_task.h"

namespace pikiwidb {

/**
 * TODO(hky): BrpcRedis is a implementation of Redis using brpc.
 * We need to parser the Resp in pstd and send msg by it
 */
class BrpcRedis : public Redis {
 public:
  void Init() { options.protocol = brpc::PROTOCOL_REDIS; }

  void Open();

  void PushRedisTask(const std::shared_ptr<RedisTask>& task);

  void Commit();

 private:
  void SetResponse(const brpc::RedisResponse& resp, const std::shared_ptr<RedisTask>& task, size_t index);

  brpc::Channel channel_;
  brpc::ChannelOptions options;
  std::mutex lock_;
  std::vector<std::shared_ptr<RedisTask>> tasks_;
  size_t batch_size_ = 5;
};
};  // namespace pikiwidb