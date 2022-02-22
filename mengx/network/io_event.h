// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/21.
//
#include <stdint.h>
#include "network/event_loop.h"

namespace mengx {
namespace network {

class IOEventCallback {
 public:
  virtual ~IOEventCallback() = default;
  virtual void EventRead() = 0;
  virtual void EventWriter() = 0;
  virtual void EventError() = 0;
  virtual void EventClose() = 0;
}

class IOEvent {
 public:
  IOEvent(EventLoop *loop, int event_fd);
  ~IoEvent();
  void EnableWriter(bool enable);
  void EnableRead(bool enable);
  void EnableError(bool enable);
  void DisableAll();
  int GetFd();
  int GetEvents();
  bool IsWritering();
  bool IsReading();
  void Handle(uint32_t events);

 private:
  void Update();

 private:
  EventLoop *loop_callback_;
  IOEventCallback *event_callback_;
  int event_fd_;
  int events_;
};

}  // namespace network
}  // namespace mengx
