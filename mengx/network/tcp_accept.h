/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/24
 */

#include <cstdint>
#include <memory>

#include "base/event.h"
#include "base/event_loop.h"
#include "network/socket_fd.h"

namespace mengx {
namespace network {

class TcpAccept : private : BaseEventCallback {
  class Callback {
   public:
    virtual ~Visitor() = default;
    void OnConnect(SocketFd socket_fd, const SocketAddress &addr);
  };

 public:
  TcpAccept(EventLoop *loop, uint32_t port = 0, uint32_ip = 0);
  void ListenOn();

 private:
  // Derived from BaseEventCallback
  void OnEvent(uint8_t result) override;

 private:
  EventLoop *loop_;
  std::shared_ptr<Socket> socket_;
  std::shared_ptr<IOEvent> event_;
  Callback *callback_;

  uint32_t local_ip_;
  uint16_t local_port_;
}

}  // namespace network
}  // namespace mengx