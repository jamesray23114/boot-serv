/*********************************************************************
 * this file (common.h) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#pragma once

#include <efi.h>
#include <efiapi.h>
#include <eficon.h>
#include <efidef.h>
#include <efiprot.h>

#define COUT ST->ConOut
#define BS   ST->BootServices

uint16 msg[67];

#define print(str) COUT->OutputString(COUT, str)
#define puti(val)  print(inttostr(msg, val, 10))
#define puth(val)  print(inttostr(msg, val, 16))
#define endl()     print(L"\n\r")

void check_status(uint16* msg, EFI_STATUS status, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST)
{
    if(status != EFI_SUCCESS) {
        print(msg);
        print(status_to_string(status));
        endl();
        while (true) ;
    }
}

