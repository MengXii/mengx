// Copyright (c) 2022 MengX done
// Author: 1542978973@qq.com

//
// Created by HJ on 2022/2/18.
//

#include "network/address_utility.h"

namespace network {

uint32_t IpToInt(const string &ip) {
  struct sockaddr_in ip_addr;
  if (inet_aton(ip.c_str(), &ip_addr.sin_addr) == 0) {
    return 0;
  }
  return ntohl(ip_addr.sin_addr.s_addr);
}

sockaddr_in ToAddress(uint32_t ip, uint16_t port) {
  sockaddr_in address;
  ::memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(ip);
  address.sin_port = htons(port);
  return address;
}
}  // namespace network
