//
//  client.h
//  Xphile-Client
//
//  Created by James Carter on 3/5/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#include <iostream>

#include <thread>

#include "log.h"
#include "string.h"

#include "prefix.h"

#include "udp.h"
#include "network.h"

namespace App {
    class Client {
    private:
        bool m_Connected = false;
        std::string m_Username;
        std::string m_ServerAddress;
        unsigned short m_ServerPort;
        App::DatagramSocket m_Connection;
        unsigned long uniqueId = -1;
    public:
        Client(std::string username, std::string server_address, unsigned short server_port);
        void send(char* data);
        void disconnect();
        inline unsigned long getId() const { return uniqueId; }
    private:
        void init();
        inline bool getConnectionStatus() { return m_Connected; }
    };
}
