//
//  sha256.cpp
//  Implementation of the SHA-256 hashing algorithm according to the Secure Hash Standard.
//  The specification can be found here:
//      https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
//
//  This implementation uses little endian byte order.
//
//  Created by Charles Wong on 2021-04-23.
//  Copyright © 2021 Charles Wong. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "sha256.h"

static const WORD k[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

void sha256(const char *message, WORD hash[]) {
    
    size_t l = strlen(message); // Message size in bytes
    size_t buffer_size = (l / 48 + 1) * 64;
    
    // Create buffer
    BYTE data[buffer_size];
    
    // Place message into buffer
    memcpy(data, message, l);
    
     // Pad data
    data[l] = 0x80;
    size_t i = l + 1;
    for (; i < buffer_size - 8; i++) {
        data[i] = 0x00;
    }
    
    size_t bitlen = l * 8;
    for (; i < buffer_size; i++) {
        data[i] = bitlen >> ((64 - i - 1) * 8);
    }
    
    // Initialize hash values
    WORD h0 = 0x6a09e667;
    WORD h1 = 0xbb67ae85;
    WORD h2 = 0x3c6ef372;
    WORD h3 = 0xa54ff53a;
    WORD h4 = 0x510e527f;
    WORD h5 = 0x9b05688c;
    WORD h6 = 0x1f83d9ab;
    WORD h7 = 0x5be0cd19;
    
    size_t num_blocks = buffer_size / 64; // number of message blocks
    
    for (int i = 0; i < num_blocks; i++) {
        WORD schedule[64];
        
        // Prepare message schedule
        for (int t = 0; t < 16; t++) {
            schedule[t] = data[i * 64 + t * 4] << 24 | data[i * 64 + t * 4 + 1] << 16 | data[i * 64 + t * 4 + 2] << 8 | data[i * 64 + t * 4 + 3];
        }
        
        for (int t = 16; t < 64; t++) {
            schedule[t] = SIGL1(schedule[t - 2]) + schedule[t - 7] + SIGL0(schedule[t - 15]) + schedule[t - 16];
        }
                
        // Initialize working vars
        WORD a = h0;
        WORD b = h1;
        WORD c = h2;
        WORD d = h3;
        WORD e = h4;
        WORD f = h5;
        WORD g = h6;
        WORD h = h7;
        
        for (int t = 0; t < 64; t++){
            WORD t1 = h + SIGU1(e) + CH(e, f, g) + k[t] + schedule[t];
            WORD t2 = SIGU0(a) + MAJ(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }
        
        // Compute intermediate hash values
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }
    
    // This implementation uses little endian, while the SHA-256 specification uses big endian.
    // Convert final hash values to big endian and write it to the output WORD array.
    hash[0] = __builtin_bswap32(h0);
    hash[1] = __builtin_bswap32(h1);
    hash[2] = __builtin_bswap32(h2);
    hash[3] = __builtin_bswap32(h3);
    hash[4] = __builtin_bswap32(h4);
    hash[5] = __builtin_bswap32(h5);
    hash[6] = __builtin_bswap32(h6);
    hash[7] = __builtin_bswap32(h7);
}
