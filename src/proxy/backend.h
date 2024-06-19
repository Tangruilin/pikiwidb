#pragma once

#include <memory>
#include "net/tcp_connection.h"

// TODO(tangruilin): 这里表示设计思路, 后续删除:
// 1. Backend 的核心功能是以后端的 pikiwidb 进行通信, 他需要保持与 pikiwidb 的长连接;
// 2. Backend 应该拥有一个自己的事件循环, 或者事件循环应该拥有一个自己的 Backend, 可能需要有多个 Backend 去共享一个
// Loop;
// 3. Backend 遇到命令的时候会去异步调用 pikiwidb 的接口, 然后通过前台传递过来的 callback, 对请求进行整理;

namespace pikiwidb {
class Backend {
 public:
  Backend() = default;
  ~Backend() = default;

  void Init();

 private:
  void Connect();

  void WriteLoop();

 private:
  std::shared_ptr<TcpConnection> conn_;
};
};  // namespace pikiwidb