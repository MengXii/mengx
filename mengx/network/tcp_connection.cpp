/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/25
 */

#include "network/tcp_connection.h"

#include "logging/log.h"

namespace mengx {
namespace network {
using logging::Log;

TcpConnection::TcpConnection(EventLoop *loop, int fd, uint32_t ip,
                             uint16_t port, Callback *callback)
    : loop_(loop),
      remote_ip_(ip),
      remote_port_(port),
      callback_(callback),
      socket_(new Socket(fd)),
      event_(new Event(loop_, fd)) {}

TcpConnection::~TcpConnection() {
  socket_->Reset();
  event_->DisableAll();
  event_->Remove();
}

void TcpConnection::SendBuffer(void *buffer, int length) {}

void TcpConnection::EventRead() {}

void TcpConnection::EventWriter() {}

void TcpConnection::EventError() { callback_->OnError(this, base::kError); }

void TcpConnection::EventClose() { callback_->OnError(this, base::kClose); }

}  // namespace network
}  // namespace mengx