/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/23
 */

#include "base/timer.h"

namespace mengx {
namespace base {

Timer::Timer(uint32_t interval_ms, Task task)
    : interval_ms_(interval_ms), task_(task) {
  UpdateTime();
}

Timer::~Timer() {}

uint64_t Timer::GetNowTimeMs() {
  struct timezone tz;
  struct timeval now;
  gettimeofday(&now, &tz);
  uint64_t ms = now.tv_sec * 1000 + now.tv_usec / 1000;
  return ms;
}

void Timer::OnEvent() {
  if (task_) {
    task_();
  }
}

void Timer::UpdateTime() {
  struct timezone tz;
  gettimeofday(&start_, &tz);
}

uint64_t Timer::GetTimeOutMs() {
  uint64_t ms = start_.tv_src * 1000 + start_.tv_usec / 1000;
  return ms;
}

}  // namespace base
}  // namespace mengx