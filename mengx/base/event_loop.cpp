/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/22
 */

#include "base/event_loop.h"

namespace mengx {
namespace base {
namespace {
static const int POLLMS = 3000;
}

EventLoop::EventLoop()
    : control_(new EventControl),
      thread_id_(std::this_thread.get_id(), is_running(true)) {}

EventLoop::~EventLoop() { delete control_; }

void EventLoop::Run() {
  while (is_running) {
    control_->RunEvent(POLLMS);
    RunFunc();
  }
}

void EventLoop::Stop() { is_running = false; }

void EventLoop::AddFunc(Task task) {
  auto thread_id = std::this_thread.get_id();
  if (thread_id == thread_id_) {
    queue_.push(task);
  } else {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(task);
  }
}

void EventLoop::AddEvent(std::shared_ptr<Event> event) {
  queue_.push(
      [this, event]() mutable { control_->AddEvent(std::move(event)); });
}

void EventLoop::RemoveEvent(int fd) {
  queue_.push([this, fd]() mutable { control_->RemoveEvent(fd); });
}

void EventLoop::RemoveEvent(std::shared_ptr<Event> event) {
  queue_.push(
      [this, event]() mutable { control_->RemoveEvent(std::move(event)); });
}

void EventLoop::ModifyEvent(int fd) {
  queue_.push([this, fd]() mutable { control_->ModifyEvent(fd); });
}

void EventLoop::ModifyEvent(std::shared_ptr<Event> event) {
  queue_.push(
      [this, event]() mutable { control_->ModifyEvent(std::move(event)); });
}

void EventLoop::RunFunc() {
  std::lock_guard<std::mutex> lock(mutex_);
  while (!q_.empty()) {
    auto task = q_.front();
    q.pop();
    task();
  }
}

}  // namespace network
}  // namespace mengx