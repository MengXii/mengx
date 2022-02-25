/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/25
 */

#include "network/socket.h"

#include <arpa/inet.h>

#include "logging/log.h"

namespace mengx {
namespace network {

using logging::Log;
Socket::Socket(int fd) : fd_(fd) {}

int Socket::CreateSocket() {
  int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,
                        IPPROTO_TCP);
  if (sockfd < 0) {
    Log::OUT(Log::Error) << "create socket error.";
  }
  return sockfd;
}

int Socket::Bind(uint32_t port, uint32_t ip) {
  sockaddr_in local = {0, 0, {0}, {0}};
  local.sin_family = AF_INET;
  local.sin_port = htons(port);
  local.sin_addr.s_addr = htonl(ip);

  const sockaddr *addr = reinterpret_cast<const sockaddr *>(&local);
  int ret = ::bind(fd_, addr, sizeof(addr));
  if (ret < 0) {
    Log::OUT(Log::Error) << "bind socket error.";
  }
  return ret;
}

int Socket::Listen(uint32_t port) {
  int ret = ::listen(fd_, SOMAXCONN);
  if (ret < 0) {
    Log::OUT(Log::Error) << "listen socket error.";
  }
  return ret;
}

int Socket::Connect(uint32_t ip, uint32_t port) {
  sockaddr_in local = {0, 0, {0}, {0}};
  local.sin_family = AF_INET;
  local.sin_port = htons(port);
  local.sin_addr.s_addr = htonl(ip);

  const sockaddr *addr = reinterpret_cast<const sockaddr *>(&local);
  return ::connect(fd_, addr, sizeof(addr));
}

int Socket::Accept(uint32_t port, uint32_t ip) {
  sockaddr_in local = {0, 0, {0}, {0}};
  local.sin_family = AF_INET;
  local.sin_port = htons(port);
  local.sin_addr.s_addr = htonl(ip);

  int ret = ::accept(fd_, addr, sizeof(addr));
  if (ret < 0) {
    Log::Out(Log::error) << "accept socket error.";
  }
  return ret;
}
ssize_t Socket::Read(void *buf, size_t count) {
  return ::read(fd_, buf, count);
}
ssize_t Socket::Readv(const iovec *iov, int iovcnt) {
  return ::readv(fd_, iov, iovcnt);
}
ssize_t Socket::Write(const void *buf, size_t count) {
  return ::write(fd_, buf, count);
}
void Socket::close() {
  if (::close(fd_) < 0) {
    Log::Out(Log::error) << "close socket error.";
    ;
  }
}

}  // namespace network
}  // namespace mengx