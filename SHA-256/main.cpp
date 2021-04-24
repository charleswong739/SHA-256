//
//  main.cpp
//  SHA-256
//
//  Created by Charles Wong on 2021-04-23.
//  Copyright © 2021 Charles Wong. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "sha256.h"

int main(int argc, const char * argv[]) {
    
    bool run = true;

    while (run) {
        std::string message;
        
        std::cout << "Message to hash: " << std::endl;
        getline(std::cin, message);
        
        WORD hash[8];
        sha256(message.c_str(), hash);
        
        for (int i = 0; i < 8; i++) {
            std::cout << std::setfill('0') << std::setw(8) << std::hex << __builtin_bswap32(hash[i]);
            
            if (i != 7) {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
        
        if (message == "q") {
            run = false;
        }
    }
        
    return 0;
}
