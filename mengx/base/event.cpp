// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/21.
//

#include "network/event.h"

#include <sys/epoll.h>
#include <unistd.h>

namespace mengx {
namespace base {

namespace {
static const int NONEVENT = 0;
static const int READEVENT = EPOLLIN | EPOLLPRI;
static const int WRITEREVENT = EPOLLOUT;
static const int ERROREVENT = EPOLLERR;
}  // namespace

void IOEventCallback::OnEvent(uint8_t result) {
  switch (result) {
    case kRead:
      EventRead();
      break;
    case kWriter:
      EventWriter();
      break;
    case kError:
      EventError();
      break;
    default:
      EventClose();
      break;
  }
}

Event::Event(EventLoop *loop, int event_fd, IOEventCallback *callback)
    : loop_(loop),
      event_callback_(callback),
      eevent_fd_(event_fd),
      events(NONEVENT) {}

void Event::EnableWriter(bool enable) {
  if (enable) {
    events_ |= WRITEREVENT;
  } else {
    events_ &= ~WRITEREVENT;
  }
  Update();
}

void Event::EnableRead(bool enable) {
  if (enable) {
    events_ |= READEVENT;
  } else {
    events_ &= ~READEVENT;
  }
  Update();
}

void Event::EnableError(bool enable) {
  if (enable) {
    events_ |= ERROREVENT;
  } else {
    events_ &= ~ERROREVENT;
  }
  Update();
}

void Event::DisableAll() {
  events_ = NONEVENT;
  Update();
}

void Event::Update() { loop_->ModifyEvent(event_fd_); }

void Event::Remove() { loop_->RemoveEvent(event_fd_); }

void Event::Handle(uint32_t events) {
  if (event_callback_ == nullptr) {
    return;
  }
  if ((events & EPOLLHUP) && !(events & EPOLLIN)) {
    event_callback_->OnEvent(kClose);
  }

  if (events & EPOLLERR) {
    event_callback_->OnEvent(kError);
  }
  if (events & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
    event_callback_->OnEvent(kRead);
  }
  if (events & EPOLLOUT) {
    event_callback_->OnEvent(kWriter);
  }
}

inline int Event::IsReading() { return events_ & READEVENT; }

inline int Event::IsWritering() { return events_ & WRITEREVENT; }

inline int Event::GetFd() { return event_fd_; }

inline int Event::GetEvents() { return events_; }

}  // namespace base
}  // namespace mengx
