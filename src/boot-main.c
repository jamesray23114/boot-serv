/*********************************************************************
 * this file (boot-main.cpp) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#include <bootserv.h>

#include "common.h"
#include "string.h"
#include "disk.h"

void efi_main(EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    EFI_SYSTEM_TABLE*  ST = SystemTable;
    EFI_STATUS         status;

    uint16* msg; BS->AllocatePool(EfiLoaderData, 66, (void**) &msg);

    BS->SetWatchdogTimer(0, 0, 0, null);
    COUT->ClearScreen(COUT);

    // load disk driver via efi

    EFI_FILE_PROTOCOL* fs = find_root(ImageHandle, ST);
    EFI_FILE_HANDLE file = open_file(fs, L"\\EFI\\BOOT\\test.txt", ImageHandle, ST);
    byte* data = read_file(file, ImageHandle, ST);

    print((uint16*) data);
    endl();

    print(L"stalling... ");
    while (true) ;
}

