// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/21.
//

#include "network/io_event.h"

#include <sys/epoll.h>
#include <unistd.h>

namespace mengx {
namespace network {

namespace {
static const int NONEVENT = 0;
static const int READEVENT = EPOLLIN | EPOLLPRI;
static const int WRITEREVENT = EPOLLOUT;
static const int ERROREVENT = EPOLLERR;
}  // namespace

IOEvent::IOEvent(int event_fd) : event_fd_(event_fd), events(NONEVENT) {}

void IOEvent::EnableWriter(bool enable) {
  if (enable) {
    events_ |= WRITEREVENT;
  } else {
    events_ &= ~WRITEREVENT;
  }
  Update();
}

void IOEvent::EnableRead(bool enable) {
  if (enable) {
    events_ |= READEVENT;
  } else {
    events_ &= ~READEVENT;
  }
  Update();
}

void IOEvent::EnableError(bool enable) {
  if (enable) {
    events_ |= ERROREVENT;
  } else {
    events_ &= ~ERROREVENT;
  }
  Update();
}

void IOEvent::DisableAll() {
  events_ = NONEVENT;
  Update();
}

void IOEvent::Update() { callback_->ModifyEvent(event_fd_); }

void IOEvent::Handle(uint32_t events) {
  if (event_callback_ == nullptr) {
    return;
  }
  if ((events & EPOLLHUP) && !(events & EPOLLIN)) {
    event_callback_->EventClose();
  }

  if (events & EPOLLERR) {
    event_callback_->EventError();
  }
  if (events & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
    event_callback_->EventRead();
  }
  if (events & EPOLLOUT) {
    event_callback_->EventWriter();
  }
}

inline int IOEvent::IsReading() { return events_ & READEVENT; }

inline int IOEvent::IsWritering() { return events_ & WRITEREVENT; }

inline int IOEvent::GetFd() { return event_fd_; }

inline int IOEvent::GetEvents() { return events_; }

}  // namespace network
}  // namespace mengx
