/*********************************************************************
 * this file (typedef.h) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#pragma once

#include "stdint.h"

#define true 1
#define false 0

#define null 0
#define nullptr (void*) 0

typedef unsigned  char        byte;
typedef unsigned  int         uint;

typedef     int8_t       int8;
typedef     int16_t     int16;
typedef     int32_t     int32;
typedef     int64_t     int64;

typedef     float       f32; // assure that f32 is 32 bits
typedef     double      f64; // assure that f64 is 64 bits

typedef     uint8_t     uint8;
typedef     uint16_t    uint16;
typedef     uint32_t    uint32;
typedef     uint64_t    uint64;

typedef     int64       intn;
typedef     uint64      uintn;

typedef     byte*       memory;

typedef     int64       bool;
typedef     uint8       aozora_status;
