//
//  udp.h
//  Xphile-Client
//
//  Created by James Carter on 3/5/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#define STR_TERM "|0"

#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "log.h"
#include "network.h"

namespace App {
    struct DatagramSocket {
    private:
        bool m_State = false;
        int file_descriptor;
        struct sockaddr_in m_Address;
        std::vector<char*> m_ReceivedMessages;
        struct sockaddr_in m_Recipient;
    public:
        bool open();
        void close();
        void send(char* data);
        void receive(const std::function<void(char*)>& call);
        void setRecipient(std::string server_address, unsigned short server_port);
    };
}
