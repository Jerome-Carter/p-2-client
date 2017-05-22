//
//  log.h
//  Xphile-Client
//
//  Created by James Carter on 3/5/17.
//  Copyright © 2017 Rome Carter Applications. All rights reserved.
//

#pragma once

#define LOGGING_ENABLED 1

#if LOGGING_ENABLED
    #define LOG(msg) std::cout << msg << std::endl
#else
    #define LOG(msg)
#endif
