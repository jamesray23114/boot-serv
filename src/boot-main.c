/*********************************************************************
 * this file (boot-main.cpp) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#include <bootserv.h>

#include "common.h"
#include "string.h"
#include "memory.h"
#include "disk.h"
#include "mmap.h"


void efi_main(EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    EFI_SYSTEM_TABLE*  ST = SystemTable;

    BS->SetWatchdogTimer(0, 0, 0, null);
    COUT->ClearScreen(COUT);

    // load disk driver via efi

    EFI_FILE_PROTOCOL* fs = find_root(ImageHandle, ST);


    multiboot2_info_table* mb2_info = (multiboot2_info_table*) malloc(1024 * 16, ImageHandle, ST);
    mb2_info += ((uintn) mb2_info) % 8 ? (8 - ((uintn) mb2_info) % 8) : 0; // align to 8 bytes, can waste up to 7 bytes of memory. 
    mb2_info->size = sizeof(multiboot2_info_table);
    mb2_info->reserved = 0;

    multiboot2_info_bootloader_name_tag* bootname = (multiboot2_info_bootloader_name_tag*) ((byte*) mb2_info + mb2_info->size);
    bootname->type = MULTIBOOT2_INFO_BOOTLOADER_NAME;
    bootname->size = sizeof(multiboot2_info_bootloader_name_tag) + sizeof("boot-serv");
    memcpy(bootname->str, "boot-serv", sizeof("boot-serv"));

    mb2_info->size += bootname->size;

    get_mmap_info(mb2_info, ImageHandle, ST);

    print(u"stalling... ");
    while (true) ;
}

