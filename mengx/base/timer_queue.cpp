/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/23
 */

#include "base/timer_queue.h"

#include <sys/timerfd.h>
#include <unistd.h>

#include <list>

#include "logging/log.h"

namespace mengx {
namespace base {

namespace {
static const int MinIntervalTimeMs = 50;
}

TimerQueue::TimerQueue(EventLoop *loop)
    : loop_(loop), fd_(CreateFd()), event_(new Event(loop_, fd_, this)) {
  loop_->AddEvnet(event_);
  event_->EnableRead(true);
  Start();
}

void TimerQueue::AddTimer(Task task, uint32_t ms, Mode mode) {
  auto timer = std::make_shared<Timer>(ms, task);
  auto time_out_ms = timer->GetTimeOutMs();
  queue_.push({time_out_ms, std::move(timer), mode});
}

int TimerQueue::CreateFd() {
  int fd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
  if (fd < 0) {
    Log::Out(Log::Error) << "Create time fd error.";
  }
  return fd;
}

void TimerQueue::Start() {
  struct itimerspec newValue;
  newValue.it_value = MinIntervalTimeMs;
  newValue.it_interval = MinIntervalTimeMs;
  int ret = ::timerfd_settime(timerFd, 0, &newValue, NULL);
  if (ret < 0) {
    Log::Out(Log::Error) << "timerfd settime error.";
  }
}

void TimerQueue::OnEvent(uint8_t result) {
  (void)result;
  std::list<TimerNode> temporary_list;
  while (!queue_.empty()) {
    auto node = queue_.top();
    if (node.timer->GetTimeOutMs() > Timer::GetNowwTimeMs()) {
      break;
    }
    node.timer->OnEvent();
    if (node.mode == kAlways) {
      auto retimer = node.timer;
      retimer->Update();
      TimerNode tempnode{node.ms, std::move(retimer), kAlways};
      temporary_list.emplace_back(std::move(tempnode));
    }
    queue_.pop();
  }
  for (auto temp : temporary_list) {
    queue_.push(std::move(temp));
  }
}

}  // namespace base
}  // namespace mengx