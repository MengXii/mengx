/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/24
 */
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "base/cpp_feature.h"
#include "network/socket_fd.h"

namespace mengx {
namespace network {
class Socket : base::NoCopyable {
 public:
  explicit Socket(int fd);

  static int CreateSocket();

  int Bind(uint16_t port = 0, uint32_t ip = 0);
  int Listen();
  int Connect(uint32_t ip, uint16_t port);
  int Accept(sockaddr_in *addr);
  ssize_t Read(void *buf, size_t count);
  static ssize_t Readv(const struct iovec *iov, int iovcnt);
  ssize_t Write(const void *buf, size_t count);
  void Close();
  int Fd();

 private:
  SocketFd fd_;
};

inline int Socket::Fd() { return fd_.Fd(); }

}  // namespace network
}  // namespace mengx