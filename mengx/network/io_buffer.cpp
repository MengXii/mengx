/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/25
 */

namespace mengx {
namespace network {
namespace {
static const uint32_t BufferMaxSize = 2048;
}

IoBuffer::IoBuffer() : store_pos_(0), fetch_pos_(0), buffer_(BufferMaxSize) {}

IoBuffer::~IoBuffer() {}

int IoBuffer::ReadFromIo(int fd, int& error_code) {
  char extrabuf[65536];
  struct iovec vec[2];
  uint32_t writable = AvailableBytes();
  vec[0].iov_base = &(*buffer_.begin()) + store_pos_;
  vec[0].iov_len = writable;
  vec[1].iov_base = extrabuf;
  vec[1].iov_len = sizeof extrabuf;

  uint32_t iovcnt = (writable < sizeof extrabuf) ? 2 : 1;
  int n = Socket::readv(fd, vec, iovcnt);
  if (n < 0) {
    error_code = errno;
  } else if ((uint32_t)n <= writable) {
    store_pos_ += n;
  } else {
    store_pos_ = buffer.size();
    append(extrabuf, n - store_pos_);
  }
  return n;
}

}  // namespace network
}  // namespace mengx