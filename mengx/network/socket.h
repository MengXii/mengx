/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/24
 */

#include <linux/tcp.h>
#include <netinet/in.h>
#include <sys/types.h>

#include "base/cpp_feature.h"

namespace mengx {
namespace network {
class Socket : base::NoCopyable {
 public:
  explicit Socket(int fd);

  static int CreateSocket();

  int Bind(uint32_t port = 0, uint32_t ip = 0);
  int Listen(uint32_t port);
  int Connect(uint32_t ip, uint32_t port);
  int Accept(uint32_t port, uint32_t ip);
  ssize_t Read(void *buf, size_t count);
  ssize_t Readv(const struct iovec *iov, int iovcnt);
  ssize_t Write(const void *buf, size_t count);
  void Close();

 private:
  int fd_;
};
}  // namespace network
}  // namespace mengx