/*********************************************************************
 * this file (mmap.h) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#pragma once

#include <bootserv.h>

#include "common.h"
#include "memory.h"
#include "disk.h"
#include "string.h"

uint32 _get_first_bit(uint32 val) {
    int i = 0;
    while(val < 32) {
        if((val << i) & 1) return i;
        val++;
    }
    return 0;
}

uint32 _get_last_bit(uint32 val) {
    int i = 31;
    while(val > 0) {
        if((val >> i) & 1) return i;
        val--;
    }
    return 0;
}

void get_gop_info(multiboot2_info_table* table, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {
    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_STATUS status = ST->BootServices->LocateProtocol(&gop_guid, nullptr, (void**)&gop);
    check_status(u"failed to locate gop protocol, error: ", status, ImageHandle, ST);

    gop->SetMode(gop, 0); 

    multiboot2_info_framebuffer_tag* gop_tag = (multiboot2_info_framebuffer_tag*) ((byte*) table + table->size);
    table->size += sizeof(multiboot2_info_framebuffer_tag) + sizeof(framebuffer_type_1); // currently only support type 1 (rgb)
    gop_tag->type = MULTIBOOT2_INFO_FRAMEBUFFER;
    gop_tag->size = sizeof(multiboot2_info_framebuffer_tag) + sizeof(framebuffer_type_1);
    gop_tag->width = gop->Mode->Info->HorizontalResolution;
    gop_tag->height = gop->Mode->Info->VerticalResolution;
    gop_tag->addr = (uint64) gop->Mode->FrameBufferBase;
    gop_tag->bpp = 32;
    gop_tag->pitch = gop->Mode->Info->PixelsPerScanLine * 4;
    gop_tag->fb_type = 1; // rgb

    if(gop->Mode->Info->PixelFormat == PixelBlueGreenRedReserved8BitPerColor) {
        framebuffer_type_1* fbinfo = (framebuffer_type_1*) gop_tag->color_info;
        fbinfo->blue_field_position = 0;
        fbinfo->blue_mask_size = 8;
        fbinfo->green_field_position = 8;
        fbinfo->green_mask_size = 8;
        fbinfo->red_field_position = 16;
        fbinfo->red_mask_size = 8;
    } else if(gop->Mode->Info->PixelFormat == PixelRedGreenBlueReserved8BitPerColor) 
    {
        framebuffer_type_1* fbinfo = (framebuffer_type_1*) gop_tag->color_info;
        fbinfo->blue_field_position = 16;
        fbinfo->blue_mask_size = 8;
        fbinfo->green_field_position = 8;
        fbinfo->green_mask_size = 8;
        fbinfo->red_field_position = 0;
        fbinfo->red_mask_size = 8;
    } else if(gop->Mode->Info->PixelFormat == PixelBitMask)
    {
        framebuffer_type_1* fbinfo = (framebuffer_type_1*) gop_tag->color_info; // no idea if this works and cannot test it
        fbinfo->blue_field_position =   _get_first_bit(gop->Mode->Info->PixelInformation.BlueMask);
        fbinfo->blue_mask_size =        _get_last_bit(gop->Mode->Info->PixelInformation.BlueMask) - fbinfo->blue_field_position + 1;
        fbinfo->green_field_position =  _get_first_bit(gop->Mode->Info->PixelInformation.GreenMask);
        fbinfo->green_mask_size =       _get_last_bit(gop->Mode->Info->PixelInformation.GreenMask) - fbinfo->green_field_position + 1;
        fbinfo->red_field_position =    _get_first_bit(gop->Mode->Info->PixelInformation.RedMask);
        fbinfo->red_mask_size =         _get_last_bit(gop->Mode->Info->PixelInformation.RedMask) - fbinfo->red_field_position + 1;
    }
    else {
        print(u"unsupported pixel format from graphics output protocol\n\r");
        ST->BootServices->Exit(ImageHandle, EFI_UNSUPPORTED, 0, nullptr);
    }
}

void get_mmap_info(multiboot2_info_table* table, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {
    uintn size = 0;
    uintn key = 0;
    EFI_MEMORY_DESCRIPTOR* buffer;

    uintn desc_size = 0;
    uint32 desc_version = 0;

    // allocate and get memory map
    EFI_STATUS status = ST->BootServices->GetMemoryMap(&size, buffer, &key, &desc_size, &desc_version);
    if (status == EFI_BUFFER_TOO_SMALL) ; 
    else check_status(u"failed to get memory map size, error: ", status, ImageHandle, ST);

    size += sizeof(EFI_MEMORY_DESCRIPTOR) * 4; 
    buffer = (EFI_MEMORY_DESCRIPTOR*) malloc(size, ImageHandle, ST);
    
    status = ST->BootServices->GetMemoryMap(&size, buffer, &key, &desc_size, &desc_version);
    check_status(u"failed to get memory map, error: ", status, ImageHandle, ST);

    uintn num_entries = size / desc_size;

    // set up multiboot2 info tables
    multiboot2_info_memory_tag* memtag = (multiboot2_info_memory_tag*) ((byte*) table + table->size);
    table->size += sizeof(multiboot2_info_memory_tag);
    memtag->type = MULTIBOOT2_INFO_MEMORY;
    memtag->size = sizeof(multiboot2_info_memory_tag);
    
    multiboot2_info_memmap_tag* mmaptag = (multiboot2_info_memmap_tag*) ((byte*) table + table->size);
    mmaptag->type = MULTIBOOT2_INFO_MEMMAP;
    mmaptag->size = sizeof(multiboot2_info_memmap_tag);
    mmaptag->entry_size = sizeof(multiboot2_mmap_entry);
    mmaptag->entry_version = 0;

    multiboot2_mmap_entry* entry = nullptr;
    bool found_lower = false;
    bool found_upper = false; // todo: this doesnt get the right value

    int j = 0;
    for(int i = 0; i < num_entries; i++)
    {
        // cannot index into buffer directly, must use this method
        EFI_MEMORY_DESCRIPTOR* curr = (EFI_MEMORY_DESCRIPTOR*)((uintn) buffer + (i * desc_size)); 
        switch(curr->Type)
        {
            case EfiReservedMemoryType:
            break;

            // usable memory
            case EfiLoaderCode:
            case EfiLoaderData:
            case EfiBootServicesCode:
            case EfiBootServicesData:
            case EfiConventionalMemory:
            case EfiPersistentMemory:
            case EfiACPIReclaimMemory:

                if (!found_lower) {
                    memtag->mem_lower = curr->PhysicalStart / 1024;
                    found_lower = true;
                }

                // check if the previous entry is the same type and if so, add the length to it
                if (j == 0) { // TODO: move this to a function
                    mmaptag->entries[j].base_addr = curr->PhysicalStart;
                    mmaptag->entries[j].length = curr->NumberOfPages * 4096;
                    mmaptag->entries[j].type = 1;
                    mmaptag->size += sizeof(multiboot2_mmap_entry);
                    j++;
                } else if (mmaptag->entries[j - 1].type == 1) {
                    mmaptag->entries[j - 1].length += curr->NumberOfPages * 4096;
                }
                else {
                    mmaptag->entries[j].base_addr = curr->PhysicalStart;
                    mmaptag->entries[j].length = curr->NumberOfPages * 4096;
                    mmaptag->entries[j].type = 1;
                    mmaptag->size += sizeof(multiboot2_mmap_entry);
                    j++;
                }
                break;

            // unusable memory
            case EfiUnusableMemory: // type 5
                if (!found_upper) {
                    memtag->mem_upper = (mmaptag->entries[j - 1].base_addr + mmaptag->entries[j - 1].length) / 1024;
                    found_upper = true;
                }
            
                if (j == 0) { // TODO: move this to a function
                    mmaptag->entries[j].base_addr = curr->PhysicalStart;
                    mmaptag->entries[j].length = curr->NumberOfPages * 4096;
                    mmaptag->entries[j].type = 5;
                    mmaptag->size += sizeof(multiboot2_mmap_entry);
                    j++;
                } else if (mmaptag->entries[j - 1].type == 5) {
                    mmaptag->entries[j - 1].length += curr->NumberOfPages * 4096;
                }
                else {
                    mmaptag->entries[j].base_addr = curr->PhysicalStart;
                    mmaptag->entries[j].length = curr->NumberOfPages * 4096;
                    mmaptag->entries[j].type = 5;
                    mmaptag->size += sizeof(multiboot2_mmap_entry);
                    j++;
                }
                break;

            case EfiMemoryMappedIO: // type 0
            case EfiMemoryMappedIOPortSpace:
                if (!found_upper) {
                    memtag->mem_upper = (mmaptag->entries[j - 1].base_addr + mmaptag->entries[j - 1].length) / 1024;
                    found_upper = true;
                }

                if (j == 0) { // TODO: move this to a function
                    mmaptag->entries[j].base_addr = curr->PhysicalStart;
                    mmaptag->entries[j].length = curr->NumberOfPages * 4096;
                    mmaptag->entries[j].type = 0;
                    mmaptag->size += sizeof(multiboot2_mmap_entry);
                    j++;
                } else if (mmaptag->entries[j - 1].type == 0) {
                    mmaptag->entries[j - 1].length += curr->NumberOfPages * 4096;
                }
                else {
                    mmaptag->entries[j].base_addr = curr->PhysicalStart;
                    mmaptag->entries[j].length = curr->NumberOfPages * 4096;
                    mmaptag->entries[j].type = 0;
                    mmaptag->size += sizeof(multiboot2_mmap_entry);
                    j++;
                }
                break;

            case EfiACPIMemoryNVS: // type 4
            case EfiRuntimeServicesCode:
            case EfiRuntimeServicesData:
            case EfiPalCode:
                if (!found_upper) {
                    memtag->mem_upper = (mmaptag->entries[j - 1].base_addr + mmaptag->entries[j - 1].length) / 1024;
                    found_upper = true;
                }

                if (j == 0) { // TODO: move this to a function
                    mmaptag->entries[j].base_addr = curr->PhysicalStart;
                    mmaptag->entries[j].length = curr->NumberOfPages * 4096;
                    mmaptag->entries[j].type = 4;
                    mmaptag->size += sizeof(multiboot2_mmap_entry);
                    j++;
                } else if (mmaptag->entries[j - 1].type == 4) {
                    mmaptag->entries[j - 1].length += curr->NumberOfPages * 4096;
                }
                else {
                    mmaptag->entries[j].base_addr = curr->PhysicalStart;
                    mmaptag->entries[j].length = curr->NumberOfPages * 4096;
                    mmaptag->entries[j].type = 4;
                    mmaptag->size += sizeof(multiboot2_mmap_entry);
                    j++;
                }
                break;
                
                default:
                    print(u"unknown memory type: ");
                    puti(curr->Type);
                    endl();
                    break;
        }
    }

    memtag->mem_upper -= 1024*1024; // standard says to subtract 1MB
    table->size += mmaptag->size;

    multiboot2_info_efi_memmap_tag *efimmaptag = (multiboot2_info_efi_memmap_tag *) ((byte*) table + table->size);
    efimmaptag->type = MULTIBOOT2_INFO_EFI_MEMMAP;
    efimmaptag->size = sizeof(multiboot2_info_efi_memmap_tag) + size;
    efimmaptag->desc_size = desc_size;
    efimmaptag->desc_version = desc_version;


    memcpy(efimmaptag->data, buffer, size);
    table->size += efimmaptag->size;
}