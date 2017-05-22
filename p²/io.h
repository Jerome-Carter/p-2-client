//
//  io.h
//  Xphile-Client
//
//  Created by James Carter on 3/7/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#include <iostream>

#include "log.h"
#include "client.h"
#include "prefix.h"

namespace App {
    class IO {
    private:
        bool running = false;
        Client* m_Client;
        std::string m_Input;
        std::string m_EncodedCmd;
        std::string m_Username;
        std::string m_ServerAddress;
        unsigned short m_ServerPort;
    public:
        IO(std::string username, std::string server_address, unsigned short server_port);
        ~IO();
    private:
        void getInput();
        void parseCmd();
    };
}
