/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/23
 */

#include <sys/time.h>

#include <cstdint>
#include <functional>
#include <memory>

#include "base/cpp_feature.h"
#include "base/types.h"

namespace mengx {
namespace base {
class Timer : private NonCopyable {
 public:
  Timer(uint32_t interval_ms, Task task);
  ~Timer();

  static uint64_t GetNowTimeMs();
  uint64_t GetTimeOutMs();
  void OnEvent();
  void UpdateTime();

 private:
  uint32_t interval_ms_;
  Task task_;
  struct timeval start_;
};
}  // namespace base
}  // namespace mengx