/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/24
 */

#include "network/tcp_accept.h"

namespace mengx {
namespace network {

TcpAccept::TcpAccept(EventLoop *loop, uint16_t port, uint32_t ip)
    : loop_(loop),
      socket_(new Socket(Socket::CreateSocket())),
      event_(new Event(loop_, socket_->Fd(), this)),
      local_port_(port),
      local_ip_(ip) {
  loop_->AddEvent(event_);
  socket_->Bind(local_port_, local_ip_);
}

TcpAccept::~TcpAccept() {
  event->DisableAll();
  event->Remove();
}

void TcpAccept::ListenOn() { socket_->Listen(); }

void TcpAccept::OnEvent() {
  sockaddr_in addr;
  int fd;
  if ((fd = socket->accept(&addr)) > 0) {
    uint32_t ip = ntohl(addr.sin_addr.s_addr);
    uint16_t port = ntons(addr.sin_port);
    callback_->OnConnect(fd, ip, port);
  }
}

}  // namespace network
}  // namespace mengx