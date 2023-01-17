/*********************************************************************
 * this file (disk.h) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#pragma once

#include "common.h"

void free(void* ptr, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {
    EFI_STATUS status = BS->FreePool(ptr);
    check_status(L"free failed: ", status, ImageHandle, ST);
}

void memset(void* ptr, byte val, uintn size) {
    for (uintn i = 0; i < size; i++) {
        ((byte*)ptr)[i] = val;
    }
}

bool memcmp(void* a, void* b, uintn size) {
    for (uintn i = 0; i < size; i++) {
        if (((byte*)a)[i] != ((byte*)b)[i]) return false;
    }
    return true;
}

void memcpy(void* dest, void* src, uintn size) {
    for (uintn i = 0; i < size; i++) {
        ((byte*)dest)[i] = ((byte*)src)[i];
    }
}

void* malloc(uintn size, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {
    void* ptr;
    EFI_STATUS status = BS->AllocatePool(EfiLoaderData, size, &ptr);
    check_status(L"malloc failed: ", status, ImageHandle, ST);
    return ptr;
}

void* calloc(uintn size, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {
    void* ptr = malloc(size, ImageHandle, ST);
    memset(ptr, 0, size);
    return ptr;
}