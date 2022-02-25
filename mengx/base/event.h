// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/21.
//
#include <cstdint>

#include "base/event_loop.h"

namespace mengx {
namespace base {

enum { kRead = 0; kWriter = 1; kError = 2; kClose = 3; }

class BaseEventCallback {
 public:
  virtual ~BaseEventCallback = default;
  virtual void OnEvent(uint8_t result) = 0;
}

class IOEventCallback : public BaseEventCallback {
 public:
  virtual ~IOEventCallback() = default;

  // Derived from BaseEventCallback
  void OnEvent(uint8_t result);
  virtual void EventRead() = 0;
  virtual void EventWriter() = 0;
  virtual void EventError() = 0;
  virtual void EventClose() = 0;
}

class Event {
 public:
  Event(EventLoop *loop, int event_fd, IOEventCallback *callback);
  ~Event();
  void EnableWriter(bool enable);
  void EnableRead(bool enable);
  void EnableError(bool enable);
  void DisableAll();
  int GetFd();
  int GetEvents();
  bool IsWritering();
  bool IsReading();
  void Handle(uint32_t events);

  void Remove();

 private:
  void Update();

 private:
  EventLoop *loop_;
  BaseEventCallback *event_callback_;
  int event_fd_;
  int events_;
};

}  // namespace base
}  // namespace mengx
