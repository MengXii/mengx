/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/22
 */

#include <sys/epoll.h>

#include <map>
#include <memory>
#include <vector>

#include "base/event.h"
#include "network/epoll.h"

namespace mengx {
namespace base {

class EventControl {
 public:
  EventControl();
  ~EventControl();
  void AddEvent(std::shared_ptr<Event> event);
  void RemoveEvent(int fd);
  void RemoveEvent(std::shared_ptr<Event> event);
  void ModifyEvent(int fd);
  void ModifyEvent(std::shared_ptr<Event> event);
  void GetEvent(int time_ms);

 private:
  void RunHandle(int cnt);

 private:
  Epoll epoll_;
  std::vector<epoll_event> event_list_;
  std::map<int, std::weak_ptr<Event>> event_poll_;
};
}  // namespace base
}  // namespace mengx