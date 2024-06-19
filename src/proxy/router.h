#pragma once

#include <memory>
#include "redis_task.h"

namespace pikiwidb {
class Router {
 public:
  Router() = default;
  virtual ~Router() = 0;

  void Dispatch(std::shared_ptr<RedisTask> task);
  virtual void Route() = 0;
};
}  // namespace pikiwidb