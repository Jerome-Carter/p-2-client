//
//  string.h
//  Xphile-Client
//
//  Created by James Carter on 3/6/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#include <iostream>

#include <vector>

namespace App {
    struct String {
        static std::string trim(const std::string& str);
        static char* strToNonConst(std::string subject);
        static char* extract_between(const char *str, const char *p1, const char *p2);
    };
}
