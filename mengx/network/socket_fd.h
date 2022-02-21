// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/18.
//

#include "base/cpp_feature.h"

namespace mengx {
namespace network {

class SocketFd : private base::NonCopyable {
 public:
  explicit SocketFd(int fd = -1) : socket_(fd) {}
  ~SocketFd() { Release(); }

  SocketFd(SocketFd &&rhs) {
    socket_ = rhs.socket_;
    rhs.socket_ = -1;
  }

  SocketFd &operator=(SocketFd &&rhs) {
    Reset(rhs.socket_);
    rhs.socket_ = -1;

    return *this;
  }

  bool Valid() const { return socket_ >= 0; }

  int Detach() {
    int tmp = socket_;
    socket_ = -1;
    return tmp;
  }

  void Reset(int fd = -1) {
    if (socket_ != fd) {
      Release();
      socket_ = fd;
    }
  }

  int Fd() const { return socket_; }

 private:
  void Release() {
    if (Valid()) {
      ::close(socket_);
    }
    socket_ = -1;
  }

 private:
  int socket_;
};

}  // namespace network
}  // namespace mengx
