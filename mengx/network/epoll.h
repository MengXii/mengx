// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/21.
//

#include <net/IOEvent.h>
#include <sys/epoll.h>

#include "base/cpp_feature.h"

namespace mengx {
namespace network {

class Epoll : private base::NonCopyable {
 public:
  Epoll();
  ~Epoll();
  bool AddEvent(IOEvent* io_event);
  bool RemoveEvent(IOEvent* io_event);
  bool ModifyEvent(IOEvent* io_event);
  bool RemoveEvent(int fd);
  int WaitEvent(epoll_event* event_list, int evenevent_sizetSize, int time_ms);

 private:
  int EpollCtrl(int operation,int fd,int events);

 private:
  int epoll_fd_;
};

}  // namespace network
}  // namespace mengx