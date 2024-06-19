#pragma once

namespace pikiwidb {

/**
 * TODO(hky): Redis will be a Interface for Redis client
 * In version 1.0, we will use cpp_redis refer to https://github.com/Cylix/cpp_redis to implement it
 **/
class Redis {
 public:
  Redis() = default;
  virtual ~Redis() = 0;
};
}  // namespace pikiwidb