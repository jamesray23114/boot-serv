/*********************************************************************
 * this file (string.h) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#pragma once
#include <typedef.h>
#include "common.h"
#include "memory.h"

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

uintn wstrlen(uint16* str) {
    uintn i = 0;
    while (str[i] != '\0') i++;
    return i * 2; // 2 bytes per char
}

uintn strlen(char* str) {
    uintn i = 0;
    while (str[i] != '\0') i++;
    return i;
}

void hd(void* ptr, uintn size, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {

    size = size % 16 ? size + 16 - (size % 16) : size;

    for (uintn i = 0; i < size; i++) {
        if (i % 16 == 0) {
            if (i != 0) {
                for (uintn j = i - 16; j < i; j++) {
                    uint16 temp[] = { 0, 0 };

                    if (((uint16*)ptr)[j] >= 0x20 && ((uint16*)ptr)[j] <= 0x7e) {
                        temp[0] = ((uint16*)ptr)[j];
                    } else {
                        temp[0] = '.';
                    }

                    print(temp);
                }
            }


            endl();

            uint16 str[9] = u"        ";
            memcpy(str, inttostr((void*) msg, ((uintn) ptr + i), 16), wstrlen(inttostr((void*) msg,((uintn) ptr + i), 16)));
            print(str);
            print(u": ");
        }

        uint16 str[6] = u"  \0\0\0"; // gcc complains if I don't add the null bytes, don't know why
        memcpy(str, inttostr((void*) msg, ((byte*)ptr)[i], 16), wstrlen(inttostr((void*) msg, ((byte*)ptr)[i], 16)));
        print(str);
        print(u" ");
    }

    for (int i = 0; i < 16; i++)
    {
        uint16 temp[] = { 0, 0 };

        if (((uint16*)ptr)[size - i - 2] >= 0x20 && ((uint16*)ptr)[size - i - 2] <= 0x7e) {
            temp[0] = ((uint16*)ptr)[size - i - 2];
        } else {
            temp[0] = '.';
        }

        print(temp);
    }
    endl();
}