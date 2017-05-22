//
//  client.cpp
//  Xphile-Client
//
//  Created by James Carter on 3/5/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include "client.h"

namespace App {
    Client::Client(std::string username, std::string server_address, unsigned short server_port)
        : m_Username(username), m_ServerAddress(server_address), m_ServerPort(server_port) {
        if (!m_Connection.open()) {
            std::cout << "The client couldn't open a connection to the server!!!" << std::endl;
        }
        m_Connection.setRecipient(m_ServerAddress, m_ServerPort);
        init();
    }
    void Client::init() {
        std::string connection_packet;
        connection_packet.append(";(CONNECTION):");
        connection_packet.append(m_Username);
        char* data = App::String::strToNonConst(connection_packet);
        m_Connection.send(data);
        delete[] data;
        m_Connected = true;
        std::thread tListen([this](){
            while (m_Connected) {
                m_Connection.receive([this](char* data){
                    if (std::string(data).compare(0, strlen(C_IN_CONN_CONF), C_IN_CONN_CONF) == 0) {
                        std::string msg = std::string(App::String::extract_between(data, C_IN_CONN_CONF, STR_TERM));
                        uniqueId = std::stoul(msg);
                        m_Connected = true;
                        LOG("Connection confirmed... ID: " << uniqueId);
                    } else if (std::string(data).compare(0, strlen(C_IN_INFO), C_IN_INFO) == 0) {
                        std::string msg = std::string(App::String::extract_between(data, C_IN_INFO, STR_TERM));
                        LOG("INFO: " << msg);
                    } else {
                        LOG(App::String::extract_between(data, "", STR_TERM));
                    }
                });
            }
        });
        tListen.detach();
    }
    void Client::send(char* data) {
        if (m_Connected) {
            m_Connection.send(data);
        }
    }
    void Client::disconnect() {
        send((char*)std::string(S_EXIT).append(std::to_string(uniqueId)).c_str());
        m_Connected = false;
        sleep(10);
        m_Connection.close();
    }
}
