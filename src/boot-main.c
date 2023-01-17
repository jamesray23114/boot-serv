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
    //EFI_FILE_HANDLE file = open_file(fs, L"\\EFI\\BOOT\\test.txt", ImageHandle, ST);
    //byte* data = read_file(file, ImageHandle, ST);


    multiboot2_info_table* mb2_info = (multiboot2_info_table*) malloc(sizeof(1024 * 16), ImageHandle, ST);
    mb2_info += ((uintn) mb2_info) % 8 ? (8 - ((uintn) mb2_info) % 8) : 0; // align to 8 bytes, wastes up to 7 bytes of memory
    mb2_info->size = sizeof(multiboot2_info_table);

    get_mmap_info(mb2_info, ImageHandle, ST);

    print(L"stalling... ");
    while (true) ;
}

