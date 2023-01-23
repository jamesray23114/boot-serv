/*********************************************************************
 * this file (common.h) is part of the boot-serv project, licensed under the GNU GPL v3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/
#pragma once

#include "bootserv.h"

char* itts(multiboot2_info_tag t) { // info tag to string
    switch (t.type) 
    {
    case MULTIBOOT2_INFO_CMDLINE:             return MULTIBOOT2_INFO_CMDLINE_STRING; break;
    case MULTIBOOT2_INFO_BOOTLOADER_NAME:     return MULTIBOOT2_INFO_BOOTLOADER_NAME_STRING; break;
    case MULTIBOOT2_INFO_MODULES:             return MULTIBOOT2_INFO_MODULES_STRING; break;
    case MULTIBOOT2_INFO_MEMORY:              return MULTIBOOT2_INFO_MEMORY_STRING; break;
    case MULTIBOOT2_INFO_BOOTDEV:             return MULTIBOOT2_INFO_BOOTDEV_STRING; break;
    case MULTIBOOT2_INFO_MEMMAP:              return MULTIBOOT2_INFO_MEMMAP_STRING; break;
    case MULTIBOOT2_INFO_VBE:                 return MULTIBOOT2_INFO_VBE_STRING; break;
    case MULTIBOOT2_INFO_FRAMEBUFFER:         return MULTIBOOT2_INFO_FRAMEBUFFER_STRING; break;
    case MULTIBOOT2_INFO_ELF_SECTIONS:        return MULTIBOOT2_INFO_ELF_SECTIONS_STRING; break;
    case MULTIBOOT2_INFO_APM_TABLE:           return MULTIBOOT2_INFO_APM_TABLE_STRING; break;
    case MULTIBOOT2_INFO_EFI_SYSTEM_TABLE:    return MULTIBOOT2_INFO_EFI_SYSTEM_TABLE_STRING; break;
    case MULTIBOOT2_INFO_EFI64_SYSTEM_TABLE:  return MULTIBOOT2_INFO_EFI64_SYSTEM_TABLE_STRING; break;
    case MULTIBOOT2_INFO_SMBIOS:              return MULTIBOOT2_INFO_SMBIOS_STRING; break;
    case MULTIBOOT2_INFO_ACPI1:               return MULTIBOOT2_INFO_ACPI1_STRING; break;
    case MULTIBOOT2_INFO_ACPI2:               return MULTIBOOT2_INFO_ACPI2_STRING; break;
    case MULTIBOOT2_INFO_NETWORK:             return MULTIBOOT2_INFO_NETWORK_STRING; break;
    case MULTIBOOT2_INFO_EFI_MEMMAP:          return MULTIBOOT2_INFO_EFI_MEMMAP_STRING; break;
    case MULTIBOOT2_INFO_BOOTSERVICES_ACTIVE: return MULTIBOOT2_INFO_BOOTSERVICES_ACTIVE_STRING; break;
    case MULTIBOOT2_INFO_EFI_IMAGE:           return MULTIBOOT2_INFO_EFI_IMAGE_STRING; break;
    case MULTIBOOT2_INFO_EFI64_IMAGE:         return MULTIBOOT2_INFO_EFI64_IMAGE_STRING; break;
    case MULTIBOOT2_INFO_IMAGE_BASE:          return MULTIBOOT2_INFO_IMAGE_BASE_STRING; break;

    default:
        return "UNKNOWN";
        break;
    }
} 

uint16_t* ittws(multiboot2_info_tag t) // info tag to wide string
{
    switch (t.type) // looks stupid, works
    {
    case MULTIBOOT2_INFO_CMDLINE:             return u"" MULTIBOOT2_INFO_CMDLINE_STRING; break;
    case MULTIBOOT2_INFO_BOOTLOADER_NAME:     return u"" MULTIBOOT2_INFO_BOOTLOADER_NAME_STRING; break;
    case MULTIBOOT2_INFO_MODULES:             return u"" MULTIBOOT2_INFO_MODULES_STRING; break;
    case MULTIBOOT2_INFO_MEMORY:              return u"" MULTIBOOT2_INFO_MEMORY_STRING; break;
    case MULTIBOOT2_INFO_BOOTDEV:             return u"" MULTIBOOT2_INFO_BOOTDEV_STRING; break;
    case MULTIBOOT2_INFO_MEMMAP:              return u"" MULTIBOOT2_INFO_MEMMAP_STRING; break;
    case MULTIBOOT2_INFO_VBE:                 return u"" MULTIBOOT2_INFO_VBE_STRING; break;
    case MULTIBOOT2_INFO_FRAMEBUFFER:         return u"" MULTIBOOT2_INFO_FRAMEBUFFER_STRING; break;
    case MULTIBOOT2_INFO_ELF_SECTIONS:        return u"" MULTIBOOT2_INFO_ELF_SECTIONS_STRING; break;
    case MULTIBOOT2_INFO_APM_TABLE:           return u"" MULTIBOOT2_INFO_APM_TABLE_STRING; break;
    case MULTIBOOT2_INFO_EFI_SYSTEM_TABLE:    return u"" MULTIBOOT2_INFO_EFI_SYSTEM_TABLE_STRING; break;
    case MULTIBOOT2_INFO_EFI64_SYSTEM_TABLE:  return u"" MULTIBOOT2_INFO_EFI64_SYSTEM_TABLE_STRING; break;
    case MULTIBOOT2_INFO_SMBIOS:              return u"" MULTIBOOT2_INFO_SMBIOS_STRING; break;
    case MULTIBOOT2_INFO_ACPI1:               return u"" MULTIBOOT2_INFO_ACPI1_STRING; break;
    case MULTIBOOT2_INFO_ACPI2:               return u"" MULTIBOOT2_INFO_ACPI2_STRING; break;
    case MULTIBOOT2_INFO_NETWORK:             return u"" MULTIBOOT2_INFO_NETWORK_STRING; break;
    case MULTIBOOT2_INFO_EFI_MEMMAP:          return u"" MULTIBOOT2_INFO_EFI_MEMMAP_STRING; break;
    case MULTIBOOT2_INFO_BOOTSERVICES_ACTIVE: return u"" MULTIBOOT2_INFO_BOOTSERVICES_ACTIVE_STRING; break;
    case MULTIBOOT2_INFO_EFI_IMAGE:           return u"" MULTIBOOT2_INFO_EFI_IMAGE_STRING; break;
    case MULTIBOOT2_INFO_EFI64_IMAGE:         return u"" MULTIBOOT2_INFO_EFI64_IMAGE_STRING; break;
    case MULTIBOOT2_INFO_IMAGE_BASE:          return u"" MULTIBOOT2_INFO_IMAGE_BASE_STRING; break;

    default:
        return u"UNKNOWN";
        break;
    }
}