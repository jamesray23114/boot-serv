/*********************************************************************
 * this file (string.h) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#pragma once
#include <typedef.h>

// uint64 to wstring
uint16* inttostr(uint16* str, uint64 val, uint base) { 
    int i = 65;
    str[66] = '\0';

    if (val == 0) {
        str[i] = '0';
        return str + i;
    }


    for (; val; i--) {
        str[i] = "0123456789abcdef"[val % base];
        val /= base;
    }

    return str + i + 1;
}