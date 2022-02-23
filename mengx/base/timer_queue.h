/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/23
 */

#include <priority_queue.h>

#include <mutex>
#include <tuple>

#include "base/event.h"
#include "base/event_loop.h"
#include "base/timer.h"

namespace mengx {
namespace base {

class TimerNode {
 public:
  enum Mode : uint8_t {
    kOnice = 0,
    kAlways = 1,
  };
  TimerNode(uint64_t ms, std::shared_ptr<Timer> timer, Mode mode = kAlways);
  ~TimerNode();

 public:
  uint64_t ms;
  Mode mode;
  std::shared_ptr<Timer> timer;
};

class TimerQueue : public ::BaseEventCallback {
 public:
  explicit TimerQueue(EventLoop* loop);
  ~TimerQueue();

  void AddTimer(Task task, uint32_t ms, Mode mode = TimerNode::kAlways);

 private:
  int CreateFd();
  bool Start();
  // Derived from BaseEventCallback
  void OnEvent(uint8_t result) override;

 private:
  EventLoop* loop_;
  int fd_;
  std::shared_ptr<Event> event_;
  std::mutex mutex;
  std::priority_queue<TimerNode> queue_;
};

inline bool operator<(TimerNode a, TimerNode b) { return a.ms > b.ms; }

}  // namespace base
}  // namespace mengx
