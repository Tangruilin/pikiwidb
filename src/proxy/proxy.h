/*
 * Copyright (c) 2023-present, Qihoo, Inc.  All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#pragma once

#include <memory>
#include "common.h"
#include "net/http_server.h"
#include "net/tcp_connection.h"

namespace pikiwidb {

/**
 * TODO(tangruilin): The PProxy class should manage the all proxy
 */
class PProxy final {
 public:
  PProxy() = default;
  ~PProxy() = default;

  PProxy& Instance();

  bool ParseArgs(int ac, char* av[]);
  const PString& GetConfigName() const { return cfg_file_; }

  bool Init();
  void Run();

  void Stop();

  void OnNewConnection(TcpConnection* obj);

 public:
  PString cfg_file_;
  uint16_t port_{0};
  PString log_level_;

  PString master_;
  uint16_t master_port_{0};

  static const uint32_t kRunidSize;

 private:
  uint32_t cmd_id_ = 0;

  std::shared_ptr<HttpServer> service_;
};
}  // namespace pikiwidb