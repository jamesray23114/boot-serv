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


    //for (int i = 0; i < mmaptag->size / sizeof(multiboot2_mmap_entry); i++) {
    //    print(u"memory type: ");
    //    puti(mmaptag->entries[i].type);
    //    print(u" addr: ");
    //    puti(mmaptag->entries[i].base_addr);
    //    print(u" -> ");
    //    puti(mmaptag->entries[i].base_addr + mmaptag->entries[i].length);
    //    endl();
    //}

    multiboot2_info_efi_memmap_tag *efimmaptag = (multiboot2_info_efi_memmap_tag *) ((byte*) table + table->size);
    efimmaptag->type = MULTIBOOT2_INFO_EFI_MEMMAP;
    efimmaptag->size = sizeof(multiboot2_info_efi_memmap_tag) + size;
    efimmaptag->desc_size = desc_size;
    efimmaptag->desc_version = desc_version;


    memcpy(efimmaptag->data, buffer, size);
    table->size += efimmaptag->size;

    hd(mmaptag, 16 * 128, ImageHandle, ST);
}