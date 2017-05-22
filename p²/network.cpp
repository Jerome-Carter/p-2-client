//
//  network.cpp
//  Xphile-Client
//
//  Created by James Carter on 3/5/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include "network.h"

namespace App {
    std::string Network::getHostnameByIp(char* ip) {
        struct hostent* hostp = gethostbyaddr((const char *)&ip, sizeof(ip), AF_INET);
        return std::string(hostp->h_name);
    }
    bool Network::getIpByHostname(const char* hostname, char* ip) {
        int i;
        struct hostent *he;
        struct in_addr **addr_list;
        if ((he = gethostbyname(hostname)) == nullptr) {
            herror("Failed to retreive host name");
            return false;
        }
        addr_list = (struct in_addr **)he->h_addr_list;
        for (i = 0; addr_list[i] != nullptr; i++) {
            strcpy(ip, inet_ntoa(*addr_list[i]));
        }
        return true;
    }
}
