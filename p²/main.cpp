//
//  main.cpp
//  Xphile-Client
//
//  Created by James Carter on 3/5/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include <iostream>

#include "io.h"

int main(int argc, const char * argv[]) {
    std::string username;
    std::string server_address;
    unsigned short server_port;
    if (argc == 4) {
        username = std::string(argv[1]);
        server_address = std::string(argv[2]);
        server_port = (unsigned short)std::strtoul(argv[3], NULL, 0);
    } else {
        std::cout << "Usage: " << argv[0] << " [username]" << " [server address]" << " [server port]" << std::endl;
        exit(-1);
    }
    LOG("Application started...");
    LOG("Provided username: " << argv[1]);
    LOG("Provided server address: " << argv[2]);
    LOG("Provided server port: " << argv[3]);
    App::IO(username, server_address, server_port);
    return 0;
}
