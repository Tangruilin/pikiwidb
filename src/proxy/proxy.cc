#include "proxy.h"

namespace pikiwidb {

PProxy& PProxy::Instance() {
  static PProxy inst_;
  return inst_;
}

// TODO(tangruilin): proxy 配置参数的初始化函数
bool PProxy::Init() { return true; }

// TODO(tangruilin): 启动 proxy 的监听, 1. 挂起对后台 pikiwidb 实例的监听; 2. 挂起对客户端的监听; 3. 通过 brpc 和 PD
// 进行沟通, 以获取集群信息
void PProxy::Run() {}

}  // namespace pikiwidb

int main() {}