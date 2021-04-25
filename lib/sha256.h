//
//  sha256.h
//  SHA-256
//
//  Created by Charles Wong on 2021-04-23.
//  Copyright © 2021 Charles Wong. All rights reserved.
//

#ifndef sha256_h
#define sha256_h

//-------MACROS-------//
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define SIGU0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SIGU1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define SIGL0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ ((x) >> 3))
#define SIGL1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ ((x) >> 10))

//-------TYPES-------//
typedef uint8_t BYTE;
typedef uint32_t WORD;

//-------FUNCTION DECS-------//
void sha256(const char *message, WORD hash[]);

#endif /* sha256_h */
