/*********************************************************************
 * this file (disk.h) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#pragma once 
#include <typedef.h>

#include "common.h"

EFI_FILE_PROTOCOL* find_root(EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {
    EFI_STATUS status;
    EFI_GUID image_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_GUID disk_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

    EFI_LOADED_IMAGE* image;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* vol;
    EFI_FILE_PROTOCOL* fs;

    status = BS->OpenProtocol(ImageHandle, &image_guid, (void**) &image, ImageHandle, nullptr, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    check_status(L"failed to find image, error: ", status, ImageHandle, ST);

    status = BS->OpenProtocol(image->DeviceHandle, &disk_guid, (void**) &vol, ImageHandle, nullptr, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
    check_status(L"failed to find file system, error: ", status, ImageHandle, ST);
    
    status = vol->OpenVolume(vol, &fs);
    check_status(L"failed to open volume, error: ", status, ImageHandle, ST);

    return fs;
}

EFI_FILE_HANDLE open_file(EFI_FILE_PROTOCOL* fs, uint16* path, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) { // file must already exist, this does not create a new file
    EFI_STATUS status;
    EFI_FILE_HANDLE file;

    status = fs->Open(fs, &file, path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);
    check_status(L"failed to open file, error: ", status, ImageHandle, ST);

    return file;
}

EFI_FILE_HANDLE create_file(EFI_FILE_PROTOCOL* fs, uint16* path, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) { 
    EFI_STATUS status;
    EFI_FILE_HANDLE file;

    status = fs->Open(fs, &file, path, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);
    check_status(L"failed to create file, error: ", status, ImageHandle, ST);

    return file;
}

byte* read_file(EFI_FILE_HANDLE file, EFI_HANDLE *ImageHandle, EFI_SYSTEM_TABLE *ST) {
    EFI_STATUS status;
    EFI_FILE_INFO* info;
    EFI_GUID info_guid = EFI_FILE_INFO_ID;
    uintn size;

    status = file->GetInfo(file, &info_guid, &size, nullptr);
    if(status == EFI_BUFFER_TOO_SMALL) ;
    else check_status(L"failed to get file info, error: ", status, ImageHandle, ST);

    status = BS->AllocatePool(EfiLoaderData, size, (void**) &info);
    check_status(L"failed to allocate pool, error: ", status, ImageHandle, ST);

    status = file->GetInfo(file, &info_guid, &size, (void**) info);
    check_status(L"failed to get file info, error: ", status, ImageHandle, ST);

    byte* file_buf;
    status = BS->AllocatePool(EfiLoaderData, info->FileSize, (void**) &file_buf);
    check_status(L"failed to allocate pool, error: ", status, ImageHandle, ST);

    size = info->FileSize;

    status = file->Read(file, &size, file_buf);
    check_status(L"failed to read file, error: ", status, ImageHandle, ST);

    return file_buf;
}

void write_file(EFI_FILE_HANDLE file, byte* data, uintn size, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {
    EFI_STATUS status;

    status = file->Write(file, &size, data);
    check_status(L"failed to write file, error: ", status, ImageHandle, ST);
}

void close_file(EFI_FILE_HANDLE file, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {
    EFI_STATUS status;

    status = file->Close(file);
    check_status(L"failed to close file, error: ", status, ImageHandle, ST);
}
