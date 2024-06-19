#pragma once

#include <memory>
#include "net/tcp_connection.h"
namespace pikiwidb {

class ProxyClient {
 public:
  ProxyClient() = default;
  ~ProxyClient() = default;

 private:
  std::shared_ptr<TcpConnection> conn_;
};
}  // namespace pikiwidb