/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/22
 */

#include "base/event_control.h"

namespace mengx {
namespace base {
namespace {
static const int KEventListCount = 32;
}

EventControl::EventControl() : event_list_(KEventListCount) {}

EventControl::~EventControl() { event_poll_.clear(); }

void EventControl::AddEvent(std::shared_ptr<Event> event) {
  event_poll_.insert({event->GetFd(), event});
  epoll_.AddEvent(event.get());
}

void EventControl::RemoveEvent(std::shared_ptr<Event> event) {
  event_poll_.erase(event.GetFd());
  epoll_.RemoveEvent(event.get())
}

void EventControl::RemoveEvent(int fd) {
  auto event = event_poll_.find(fd);
  if (event != event_poll_end()) {
    epoll_.RemoveEvent(fd);
    event_poll_.erase(fd);
  }
}

void EventControl::ModifyEvent(std::shared_ptr<Event> event) {
  int fd = event->GetFd();
  auto it = event_poll_.find(fd);
  if (it != event_poll_.end()) {
    event_poll_[fd] = event;
    epoll_.ModifyEvent(event.get());
  }
}

void EventControl::ModifyEvent(int fd) {
  auto it = event_poll_.find(fd);
  if (it != event_poll_.end()) {
    auto event = it->second.lock();
    if (event) {
      epoll_.ModifyEvent(event.get());
    }
  }
}

void EventControl::RunEvent(int time_ms) {
  int cnt = epoll_.WaitEvent(&*event_list_.begin(), event_list_.size(), timeMs);
  if (cnt < 0) {
    return;
  }
  RunHandle(cnt);
}

void EventControl::RunHandle(int cnt) {
  for (int i = 0, i < cnt, i++) {
    int fd = event_list_[i].data.fd;
    auto event = event_poll[fd].lock();
    if (event) {
      event->Handle(event_list_[i].events);
    } else {
      ModifyEvent(fd);
    }
  }
}

}  // namespace network
}  // namespace mengx