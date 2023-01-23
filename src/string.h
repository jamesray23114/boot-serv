/*********************************************************************
 * this file (string.h) is part of the boot-serv project, licensed under the GNU GPLv3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/

#pragma once
#include <typedef.h>
#include <util.h>

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

uintn wstrlen(uint16* str) { // returns the length of a wstring in bytes, not characters. divide by 2 to get the number of characters
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

void print_info_tag_ex(multiboot2_info_tag* tag, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {

    switch (tag->type)
    {
    case MULTIBOOT2_INFO_CMDLINE:
        multiboot2_info_cmdline_tag* cmd = (multiboot2_info_cmdline_tag*) tag;
        print(u"    cmdline: ");
        for(int i = 0; i < strlen(cmd->cmdline); i++) {
            uint16 temp[] = { 0, 0 };
            temp[0] = cmd->cmdline[i];
            print(temp);
        }
        endl();
        break;
    
    case MULTIBOOT2_INFO_BOOTLOADER_NAME:
        multiboot2_info_bootloader_name_tag* bln = (multiboot2_info_bootloader_name_tag*) tag;
        print(u"    bootloader name: ");
        for(int i = 0; i < strlen(bln->str); i++) {
            uint16 temp[] = { 0, 0 };
            temp[0] = (uint16) bln->str[i];
            print(temp);
        }
        endl();
        break;

    case MULTIBOOT2_INFO_MEMORY:
        multiboot2_info_memory_tag* mem = (multiboot2_info_memory_tag*) tag;
        print(u"    start address: ");
        puti(mem->mem_lower);
        endl();
        print(u"    end address:   ");
        puti(mem->mem_upper / 1024 / 1024);
        print(u" MB");
        endl();
        break;

    case MULTIBOOT2_INFO_MEMMAP:
        multiboot2_info_memmap_tag* mmap = (multiboot2_info_memmap_tag*) tag;
        print(u"    memory map:");
        endl();
        for (int i = 0; i < mmap->size / sizeof(multiboot2_mmap_entry); i++) {
            print(u"        memory type: ");
            puti(mmap->entries[i].type);
            print(u" addr: ");
            puth(mmap->entries[i].base_addr);
            print(&(u"         "[wstrlen(inttostr(msg, mmap->entries[i].base_addr, 16)) / 2]));
            print(u" -> ");
            puth(mmap->entries[i].base_addr + mmap->entries[i].length);
            endl();
        }
        break;

    case MULTIBOOT2_INFO_FRAMEBUFFER:
        multiboot2_info_framebuffer_tag* fb = (multiboot2_info_framebuffer_tag*) tag;
        print(u"    framebuffer:");
        endl();
        print(u"        addr: ");
        puth(fb->addr);
        endl();
        print(u"        pitch: ");
        puti(fb->pitch);
        endl();
        print(u"        width: ");
        puti(fb->width);
        endl();
        print(u"        height: ");
        puti(fb->height);
        endl();
        print(u"        bpp: ");
        puti(fb->bpp);
        endl();
        break;

    default:
        break;
    }
}



void print_info_tags(multiboot2_info_table* table, bool ex, EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* ST) {

    uintn size = table->size - sizeof(multiboot2_info_table);

    print(u"printing info tags:");
    print(u"                          size: ");
    puti(size);
    endl();

    while (size > 0) {
        multiboot2_info_tag* tag = (multiboot2_info_tag*) table->tags;
        print(u"tag type: ");
        print(ittws(*tag));

        print(&(u"                                  "[wstrlen(ittws(*tag)) / 2])); // this is a hacky way to align strings

        print(u" size: ");
        puti(tag->size);
        endl();

        if (ex)
            print_info_tag_ex(tag, ImageHandle, ST);

        size -= tag->size;
        table = (void*) ((uintn) table + tag->size);


        uintn ccol = ST->ConOut->Mode->CursorColumn;
        print(u"press any key to continue...");
        wait_for_key(ImageHandle, ST);
        print(u"\r");
    }

    print(u"                             \r"); // remove the "press any key to continue..." message
}