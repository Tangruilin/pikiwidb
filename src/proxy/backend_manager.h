#pragma once

#include <memory>
#include <vector>
#include "proxy/backend.h"

namespace pikiwidb {

class BackendManager {
 public:
  BackendManager() = default;
  ~BackendManager() = default;

  void Init();
  void Run();
  void Stop();

  void Register();

 private:
  std::vector<std::shared_ptr<Backend>> backends_;
};
}  // namespace pikiwidb