//
//  network.h
//  Xphile-Client
//
//  Created by James Carter on 3/5/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#include <iostream>

#include <netdb.h>
#include <arpa/inet.h>

namespace App {
    class Network {
    public:
        static std::string getHostnameByIp(char *ip);
        static bool getIpByHostname(const char* hostname, char* ip);
    };
}
