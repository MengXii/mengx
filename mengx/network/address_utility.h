// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/18.
//

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>

#include <string>

namespace mengx {
namespace network {
using std::string;

uint32_t IpToInt(const string &ip);
sockaddr_in ToAddress(uint32_t ip, uint16_t port);
};  // namespace network
}  // namespace mengx
