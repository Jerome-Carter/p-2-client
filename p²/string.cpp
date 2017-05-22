//
//  string.cpp
//  Xphile-Client
//
//  Created by James Carter on 3/6/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#include "string.h"

namespace App {
    std::string String::trim(const std::string& str)
    {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first)
        {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
    char* String::strToNonConst(std::string subject) {
        char* result = new char[subject.size()];
        strcpy(result, subject.c_str());
        return result;
    }
    char* String::extract_between(const char *str, const char *p1, const char *p2) {
        const char *i1 = strstr(str, p1);
        if (i1 != NULL) {
            const size_t pl1 = strlen(p1);
            const char *i2 = strstr(i1 + pl1, p2);
            if (p2 != NULL) {
                /* Found both markers, extract text. */
                const size_t mlen = i2 - (i1 + pl1);
                char* ret = (char*)malloc(mlen + 1);
                if (ret != NULL) {
                    memcpy(ret, i1 + pl1, mlen);
                    ret[mlen] = '\0';
                    return ret;
                }
            }
        }
        return (char*)std::string("").c_str();
    }
}
