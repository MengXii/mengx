// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/18.
//

namespace base {

class NonCopyable {
 public:
  NonCopyable();
  ~NonCopyable();
  NonCopyable(NonCopyable &&) {}
  NonCopyable &operator=(NonCopyable &&) { return *this; }

 private:
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable &operator=(const NonCopyable &) = delete;
};

class NonMovable {
 public:
  NonMovable();
  ~NonMovable();

 private:
  NonMovable(NonMovable &&) = delete;
  NonMovable &operator=(NonMovable &&) = delete;
};

class NonCopyOrMovable {
 protected:
  NonCopyOrMovable() {}
  ~NonCopyOrMovable() {}

 private:
  NonCopyOrMovable(const NonCopyOrMovable &) = delete;
  NonCopyOrMovable(NonCopyOrMovable &&) = delete;
  NonCopyOrMovable &operator=(const NonCopyOrMovable &) = delete;
  NonCopyOrMovable &operator=(NonCopyOrMovable &&) = delete;
};

}  // namespace base