/*
 * Copyright (C) 2022-2022 MengX done
 *
 * Author: 1542978973@qq.com
 * Created by HJ on 2022/02/25
 */

#include <memory>
#include <string>

#include "base/event.h"
#include "base/event_loop.h"
#include "network/socket.h"
#include "network/io_buffer.h"

namespace mengx {
namespace network {
using base::EventLoop;

class TcpConnection : private base::IOEventCallback {
 public:
  class Callback {
    // This connection was closed by the remote peer.
    virtual void OnError(TcpConnection *conn, int events) = 0;

    virtual void OnBufferReceived(TcpConnection *conn, void *buffer) = 0;

   protected:
    virtual ~TcpConnectionCallback() {}
  };

  TcpConnection(EventLoop *loop, int fd, uint32_t remote_ip,
                uint16_t remote_port, Callback *callback);

  ~TcpConnection();

  void SendBuffer(void *buffer, int length);

 private:
  // Derived from base::IoEventCallback
  void EventRead() override;
  void EventWriter() override;
  void EventError() override;
  void EventClose() override;

 private:
  EventLoop *loop_;

  // remote address
  uint32_t remote_ip_;
  uin16_t remote_port_;

  Callback *callback_;

  std::shared_ptr<Socket> socket_;
  std::shared_ptr<Event> event_;

  IOBuffer read_buffer_;
  IOBuffer writer_buffer_;
}
}  // namespace network
}  // namespace mengx