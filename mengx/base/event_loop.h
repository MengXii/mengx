/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/22
 */

#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include "base/event.h"
#include "base/event_control.h"

namespace mengx {
namespace network {

class EventLoop {
 public:
  EventLoop();
  ~EventLoop();

  void AddFunc(Task task);
  void AddEvent(std::shared_ptr<Event> event);
  void RemoveEvent(std::shared_ptr<Event> event);
  void ModifyEvent(std::shared_ptr<Event> event);
  void ModifyEvent(int fd);
  void RemoveEvent(int fd);
  void Run();
  void Stop();

 private:
  void RunFunc();

 private:
  EventControl* control_;
  std::thread::id thread_id_;
  bool is_running;
  std::mutex mutex_;
  std::queue<Task> queue_;
};

}  // namespace network
}  // namespace mengx