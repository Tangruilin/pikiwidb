#pragma once

#include <thread>
#include <vector>
#include "io_thread_pool.h"

namespace pikiwidb {

// ProxyIOThreadPool is EventLoop for Proxy, it will deal with the IO event for Proxy
class ProxyIOThreadPool : public IOThreadPool {
 public:
  ProxyIOThreadPool() = default;
  ~ProxyIOThreadPool() = default;

  void Exit() override;
  // void PushWriteTask(std::shared_ptr<PClient> client) override;

 private:
  void StartWorkers() override;

 private:
  std::vector<std::thread> writeThreads_;
  std::vector<std::unique_ptr<std::mutex>> writeMutex_;
  std::vector<std::unique_ptr<std::condition_variable>> writeCond_;
  // std::vector<std::deque<std::shared_ptr<PClient>>> writeQueue_;
  std::atomic<uint64_t> counter_ = 0;
  bool writeRunning_ = true;
};
}  // namespace pikiwidb