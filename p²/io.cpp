//
//  io.cpp
//  Xphile-Client
//
//  Created by James Carter on 3/7/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include "io.h"

namespace App {
    IO::IO(std::string username, std::string server_address, unsigned short server_port)
        : m_Username(username), m_ServerAddress(server_address), m_ServerPort(server_port) {
        m_Client = new Client(username, server_address, server_port);
        running = true;
        while (running) {
            getInput();
            bool send = true;
            if (m_Input.compare(0, strlen(C_EXIT), C_EXIT) == 0) {
                m_Client->disconnect();
                send = false;
            }
            if (send) {
                m_Client->send((char*)m_Input.c_str());
            }
        }
    }
    IO::~IO() {
        delete m_Client;
    }
    void IO::getInput() {
        std::getline(std::cin, m_Input);
    }
}
