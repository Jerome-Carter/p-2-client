//
//  udp.cpp
//  Xphile-Client
//
//  Created by James Carter on 3/5/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include "udp.h"

namespace App {
    bool DatagramSocket::open() {
        if ((file_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
            perror("Failed to create socket");
            return false;
        }
        LOG("Datagram socket created. Its file descriptor is " << std::to_string(file_descriptor));
        memset((void*)&m_Address, 0, sizeof(m_Address));
        m_Address.sin_family = AF_INET;
        m_Address.sin_addr.s_addr = htonl(INADDR_ANY);
        m_Address.sin_port = htons(0);
        LOG("Socket m_Address assigned to " << inet_ntoa(m_Address.sin_addr) << ":" << std::to_string(ntohs(0)));
        if ((bind(file_descriptor, (struct sockaddr*)&m_Address, sizeof(m_Address))) < 0) {
            perror("Failed to bind socket");
            return false;
        }
        LOG("Socket bound");
        unsigned int addr_length = sizeof(m_Address);
        if (getsockname(file_descriptor, (struct sockaddr *)&m_Address, &addr_length) < 0) {
            perror("Failed to retreive socket name");
            return false;
        }
        LOG("Socket created and bound to " << inet_ntoa(m_Address.sin_addr) << ":" << ntohs(m_Address.sin_port));
        m_State = true;
        return true;
    }
    void DatagramSocket::send(char* data) {
        if (m_State) {
            std::thread tSend([this, data] () {
                char* msg = (char*)std::string(std::string(data) + STR_TERM).c_str();
                long bytes_sent;
                unsigned long len = std::strlen(msg);
                if ((bytes_sent = sendto(file_descriptor, msg, len, 0, (struct sockaddr*)&m_Recipient, sizeof(struct sockaddr))) < 0) {
                    if (m_State) {
                        perror("Failed to send data");
                    }
                }
            });
            tSend.detach();
        }
    }
    void DatagramSocket::receive(const std::function<void(char*)>& call) {
        if (m_State) {
            char data[1024];
            long bytes_recved;
            socklen_t addr_len = sizeof(m_Recipient);
            if ((bytes_recved = recvfrom(file_descriptor, data, sizeof(data), 0, (struct sockaddr*)&m_Recipient, &addr_len)) < 0) {
                if (m_State) {
                    perror("Failed to receive data");
                }
            }
            m_ReceivedMessages.push_back(data);
            call(data);
            bzero(data, 1024);
        }
    }
    void DatagramSocket::setRecipient(std::string server_m_Address, unsigned short server_port) {
        const char* hostname = server_m_Address.c_str();
        char ip[100];
        if (Network::getIpByHostname(hostname, ip)) {
            LOG("Provided hostname " << server_m_Address << " resolved to " << ip);
            server_m_Address = ip;
        } else {
            std::cout << "Couldn't resolve IP from hostname " << server_m_Address << ", so the server m_Address is set to localhost";
            server_m_Address = "127.0.0.1";
        }
        memset((void*)&m_Recipient, 0, sizeof(m_Recipient));
        m_Recipient.sin_family = AF_INET;
        m_Recipient.sin_addr.s_addr = inet_addr(server_m_Address.c_str());
        m_Recipient.sin_port = htons(server_port);
        LOG("Socket recipient set to " << inet_ntoa(m_Recipient.sin_addr) << ":" << ntohs(m_Recipient.sin_port));
    }
    void DatagramSocket::close() {
        if (m_State) {
            m_State = false;
            if (::close(file_descriptor) < 0) {
                perror("Failed to close socket!");
            } else LOG("Socket closed!");
        }
    }
}
