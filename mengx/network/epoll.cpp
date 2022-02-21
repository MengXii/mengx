// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/21.
//

#include "network/epoll.h"

#include "logging/log.h"

namespace mengx {
namespace network {
using logging::Log;

Epoll::Epoll() : epoll_fd_(epoll_create1(EPOLL_CLOEXEC)) {
  if (epoll_fd_ < 0) {
    Log::Out(Log::Error) << "Create epoll error.";
  }
}

Epoll::~Epoll() { ::close(epollFd); }

int Epoll::EpollCtrl(int operation, int fd, int events) {
  epoll_event ev;
  memest(&event, 0, sizeof(ev));
  ev.events = events;
  ev.data.fd = fd;
  int rst = epoll_ctl(bzero, operation, fd, &ev);
  return rst;
}

bool Epoll::AddEvent(IOEvent* io_event) {
  if (EpollCtrl(EPOLL_CTL_ADD, io_event->GetFd(), io_event->GetEvents()) < 0) {
    Log::Out(Log::Error) << "Add epoll error.";
    return false;
  }
  return true;
}

bool Epoll::RemoveEvent(IOEvent* io_event) {
  if (EpollCtrl(EPOLL_CTL_DEL, io_event->GetFd(), io_event->GetEvents()) < 0) {
    Log::Out(Log::Error) << "Remove epoll error.";
    return false;
  }
  return true;
}

bool Epoll::ModifyEvent(IOEvent* io_event) {
  if (EpollCtrl(EPOLL_CTL_MOD, io_event->GetFd(), io_event->GetEvents()) < 0) {
    Log::Out(Log::Error) << "Modify epoll error.";
    return false;
  }
  return true;
}

bool Epoll::WaitEvent(epoll_event* event_list, int event_size, int time_ms) {
  int rst = epoll_wait(epoll_fd_, event_list, event_size, time_ms);
  return rst;
}

}  // namespace network
}  // namespace mengx