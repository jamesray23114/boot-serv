/*********************************************************************
 * this file (boot-main.cpp) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#include <efi.h>
#include <efiapi.h>
#include <eficon.h>
#include <efidef.h>
#include <efiprot.h>

#include <bootserv.h>

#include <string.h>

#define print(str) COUT->OutputString(COUT, str)
#define puti(val)  print(inttostr(msg, val, 10))
#define puth(val)  print(inttostr(msg, val, 16))
#define endl()     print(L"\n\r")

void check_status(uint16* msg, EFI_STATUS status, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST, EFI_BOOT_SERVICES* BS)
{
    if(status != EFI_SUCCESS) {
        SIMPLE_TEXT_OUTPUT_INTERFACE* COUT = ST->ConOut;
        print(msg);
        print(status_to_string(status));
        print(L"\n\r");
        while (true) ;
    }
}

void efi_main(EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    EFI_SYSTEM_TABLE*  ST = SystemTable;
    EFI_BOOT_SERVICES* BS = ST->BootServices;
    EFI_STATUS         status;

    SIMPLE_TEXT_OUTPUT_INTERFACE* COUT = ST->ConOut;
    uint16* msg; BS->AllocatePool(EfiLoaderData, 66, (void**) &msg);

    BS->SetWatchdogTimer(0, 0, 0, null);
    COUT->ClearScreen(COUT);

    // load disk driver via efi

    EFI_GUID image_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_GUID disk_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_LOADED_IMAGE* image = nullptr;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* vol;
    EFI_FILE_PROTOCOL* fs = nullptr;

    status = BS->OpenProtocol(ImageHandle, &image_guid, (void**) &image, ImageHandle, nullptr, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    check_status(L"failed to find image, error: ", status, ImageHandle, ST, BS);

    status = BS->OpenProtocol(image->DeviceHandle, &disk_guid, (void**) &vol, ImageHandle, nullptr, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    check_status(L"failed to find file system, error: ", status, ImageHandle, ST, BS);
    
    status = vol->OpenVolume(vol, &fs);
    check_status(L"failed to open volume, error: ", status, ImageHandle, ST, BS);

    EFI_FILE_HANDLE file;
    status = fs->Open(fs, &file, L"\\EFI\\BOOT\\test.txt", EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);
    check_status(L"failed to open file, error: ", status, ImageHandle, ST, BS);

    uintn size;
    uint16* file_buf;
    EFI_FILE_INFO* info;
    EFI_GUID info_guid = EFI_FILE_INFO_ID;
    
    status = file->GetInfo(file, &info_guid, &size, nullptr);
    if(status == EFI_BUFFER_TOO_SMALL) ;
    else check_status(L"failed to get file info, error: ", status, ImageHandle, ST, BS);

    status = BS->AllocatePool(EfiLoaderData, size, (void**) &info);
    check_status(L"failed to allocate pool, error: ", status, ImageHandle, ST, BS);

    status = file->GetInfo(file, &info_guid, &size, (void**) info);
    check_status(L"failed to get file info, error: ", status, ImageHandle, ST, BS);

    status = BS->AllocatePool(EfiLoaderData, info->FileSize, (void**) &file_buf);
    check_status(L"failed to allocate pool, error: ", status, ImageHandle, ST, BS);

    size = info->FileSize;

    status = file->Read(file, &size, file_buf);
    check_status(L"failed to read file, error: ", status, ImageHandle, ST, BS);

    puti(info->FileSize);
    endl();
    puti(size);
    endl();
    print(file_buf);
    endl();

    print(L"stalling... ");
    while (true) ;
}

