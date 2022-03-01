/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/25
 */

#include <cstdint>
#include <vector>

namespace mengx {
namespace network {

class IoBuffer {
 public:
  IoBuffer();
  ~IoBuffer();

  int ReadFromIo(int fd, int &error_code);

  uint32_t AvailableBytes();
  uint32_t StoredBytes() const;

  bool Empty();

  void Append(const char *data, std::: size_t length);
  void Append(const std::string &str);

  void ResizeBuffer(int len);

  void Reset();

  int ReadAll(std::vector<uint8_t> &data);
  int Read(std::vector<uint8_t> &data, uint32_t len);
  int Read(std::string &data, uint32_t len);
  void Swap(Buffer &rhs);

 private:
  const uint8_t *Begin() const;
  void UpdateIndex(uint32_t len);

 private:
  uint32_t store_pos_;
  uint32_t fetch_pos_;
  std::vector<uint8_t> buffer_;
}
}  // namespace network
}  // namespace mengx