/*********************************************************************
 * this file (bootserv.h) is part of the boot-serv project, licensed under the GNU GPL v3
 * source code available at https://github.com/jamesray23114/boot-serv 
 * 
 * refer to the LICENSE file for more information
**********************************************************************/
#pragma once

#include <stdint.h>

// =================================================================================================
// DEFINES
// =================================================================================================

#ifndef MULTIBOOT2_HEADER
#define MULTIBOOT2_HEADER 1

#define MULTIBOOT2_ALIGN 8
#define MULTIBOOT2_SEARCH 32768

#define MULTIBOOT2_HEADER_MAGIC 0xE85250D6

// =================================================================================================
// MULTIBOOT2 HEADER
// =================================================================================================

typedef struct {
    uint32_t magic; // 0xE85250D6
    uint32_t architecture; // 0 = x86, 4 = 32-bit mips
    uint32_t header_length; 
    uint32_t checksum;
    multiboot2_tag tags[]; // must end with a tag of type 0 and size 8   
} __attribute__ ((__packed__)) multiboot2_header;
#define MULTIBOOT2_EAX_MAGIC 0x2BADB002
#define MULTIBOOT2_ARCHITECTURE_X86 0
#define MULTIBOOT2_ARCHITECTURE_MIPS32 4

typedef struct {
    uint16_t type;
    uint16_t flags; // may avoid loading if bit zero is set
    uint32_t size;
    uint8_t data[];
} __attribute__ ((__packed__)) multiboot2_tag;

typedef struct {
    uint16_t type; // 1
    uint16_t flags; 
    uint32_t size;
    uint32_t tags[]; // info tags requested by the kernel, the value refering to the type of the tag
} __attribute__ ((__packed__)) multiboot2_request_tag; // refer to MULTIBOOT2 INFO STRUCTURE below
#define MULTIBOOT2_TAG_REQUEST 1

typedef struct {
    uint16_t type; // 2
    uint16_t flags; // must pass info to kernel if image is not in elf format
    uint32_t size;
    uint32_t header_addr;   // physical address of the multi-boot header
    uint32_t load_addr;     // physical address of the text segment
    uint32_t load_end_addr; // end address of the data segment
    uint32_t bss_end_addr;  // end address of the bss segment
} __attribute__ ((__packed__)) multiboot2_address_tag;
#define MULTIBOOT2_TAG_ADDRESS 2

typedef struct {
    uint16_t type; // 3
    uint16_t flags; 
    uint32_t size;
    uint32_t entry_addr; // physical address of the entry point
} __attribute__ ((__packed__)) multiboot2_entry_tag;
#define MULTIBOOT2_TAG_ENTRY 3

typedef struct {
    uint16_t type; // 4
    uint16_t flags; 
    uint32_t size; // 12
    uint32_t consoleflags; 
        // bit 0: information about console must be provided in the multiboot2 info structure 
        // bit 1: os image supports ega text mode
} __attribute__ ((__packed__)) multiboot2_console_tag;
#define MULTIBOOT2_TAG_CONSOLE 4

typedef struct {
    uint16_t type; // 5
    uint16_t flags; 
    uint32_t size; // 20
    uint32_t width;     // number of columns / pixels
    uint32_t height;    // number of lines / pixels
    uint32_t depth;     // number of bits per pixel, 0 if in text mode or os doesnt care
} __attribute__ ((__packed__)) multiboot2_framebuffer_tag;
#define MULTIBOOT2_TAG_FRAMEBUFFER 5

typedef struct {
    uint16_t type; // 6
    uint16_t flags; 
    uint32_t size; // 8
} __attribute__ ((__packed__)) multiboot2_module_alignment_tag; // if present modules must be page aligned
#define MULTIBOOT2_TAG_MODULE_ALIGNMENT 6

typedef struct {
    uint16_t type; // 7
    uint16_t flags; 
    uint32_t size; // 8
} __attribute__ ((__packed__)) multiboot2_bootservices_tag; // if present the kernel can start before efi boot services are terminated
#define MULTIBOOT2_TAG_BOOTSERVICES 7

typedef struct {
    uint16_t type; // 8
    uint16_t flags; 
    uint32_t size;
    uint32_t entry_addr; // physical address of the entry point, should only be done if the header contains a efi boot services tag
} __attribute__ ((__packed__)) multiboot2_efi_entry_tag;
#define MULTIBOOT2_TAG_EFI_ENTRY 8

typedef struct {
    uint16_t type; // 9
    uint16_t flags; 
    uint32_t size;
    uint32_t entry_addr; // physical address of the entry point, should only be done if the header contains a efi boot services tag
} __attribute__ ((__packed__)) multiboot2_x86_64_efi_entry_tag;
#define MULTIBOOT2_TAG_X86_64_EFI_ENTRY 9

typedef struct {
    uint16_t type; // 10
    uint16_t flags; 
    uint32_t size; // 24
    uint32_t min_addr;   // the lowest address that can be used for the kernel
    uint32_t max_addr;   // the highest address that can be used for the kernel
    uint32_t align;      // the alignment of the kernel
    uint32_t preference; // the preferred address of the kernel, 0 if no preference, 1 at the lowest address, 2 at the highest address. 
} __attribute__ ((__packed__)) multiboot2_relocation_tag;
#define MULTIBOOT2_TAG_RELOCATION 10

// =================================================================================================
// MULTIBOOT2 INFO STRUCTURE
// =================================================================================================

typedef struct {
    uint32_t size;
    uint32_t reserved;
    multiboot2_info_tag tags[]; // must end with a tag of type 0 and size 8
} __attribute__ ((__packed__)) multiboot2_info_table;
#define MULTIBOOT2_INFO_END {0, 8}

typedef struct {
    uint32_t type;
    uint32_t size;
    uint8_t data[];
} __attribute__ ((__packed__)) multiboot2_info_tag;

typedef struct {
    uint32_t type; // 1
    uint32_t size; 
    char cmdline[]; // null terminated string 
} __attribute__ ((__packed__)) multiboot2_info_cmdline_tag;
#define MULTIBOOT2_INFO_CMDLINE 1

typedef struct 
{
    uint32_t type; // 2
    uint32_t size; 
    char str[]; // null terminated string
} __attribute__ ((__packed__)) multiboot2_info_bootloader_name_tag; 
#define MULTIBOOT2_INFO_BOOTLOADER_NAME 2

typedef struct {
    uint32_t type; // 3
    uint32_t size; 
    uint32_t mod_start; // physical address of the module
    uint32_t mod_end;   // physical address of the end of the module
    char str[];         // null terminated string
} __attribute__ ((__packed__)) multiboot2_info_modules_tag;
#define MULTIBOOT2_INFO_MODULES 3

typedef struct {
    uint32_t type; // 4
    uint32_t size; // 16
    uint32_t mem_lower; // in kilobytes, maximum value is 640
    uint32_t mem_upper; // in kilobytes, lowest value is 1024
} __attribute__ ((__packed__)) multiboot2_info_memory_tag;
#define MULTIBOOT2_INFO_MEMORY 4

typedef struct {
    uint32_t type; // 5
    uint32_t size; // 20
    uint32_t biosdev;       // bios device number
    uint32_t partition;     // bios slice number
    uint32_t sub_partition; // bios partition number
} __attribute__ ((__packed__)) multiboot2_info_bootdev_tag;
#define MULTIBOOT2_INFO_BOOTDEV 5

typedef struct {
    uint32_t type; // 6
    uint32_t size; 
    uint32_t entry_size;            // size of one entry
    uint32_t entry_version;         // 0
    multiboot2_mmap_entry memory[]; // array of memory regions, refer to MULTIBOOT2 MEMORY STRUCTURE below
} __attribute__ ((__packed__)) multiboot2_info_memmap_tap;
#define MULTIBOOT2_INFO_MEMMAP 6

typedef struct { // bios thing, dont care for now
    uint32_t type; // 7
    uint32_t size; // 784 
    uint16_t mode;
    uint16_t interface_seg;
    uint16_t interface_off;
    uint16_t interface_len;
    uint8_t  control_info[512];
    uint8_t  mode_info[256];
} __attribute__ ((__packed__)) multiboot2_info_vbe_tag;
#define MULTIBOOT2_INFO_VBE 7

typedef struct {
    uint32_t type; // 8
    uint32_t size; 
    uint64_t addr;   // physical address of the framebuffer 
    uint32_t pitch;  // number of bytes per line
    uint32_t width;  // number of pixels per line
    uint32_t height; // number of lines
    uint8_t bpp;     // bits per pixel
    uint8_t type;    // 0 = indexed, 1 = rgb, 2 = ega text
    uint8_t reserved; 
    uint8_t color_info[]; // nothing for 2, refer to MULTIBOOT2 FRAMEBUFFER TAG below for others
} __attribute__ ((__packed__)) multiboot2_info_framebuffer_tag;
#define MULTIBOOT2_INFO_FRAMEBUFFER 8

typedef struct {
    uint32_t type; // 9
    uint32_t size; 
    uint16_t num;        // number of entries
    uint16_t entry_size; // size of all entry
    uint16_t shndx;      // index of the section header string table
    uint16_t reserved; 
    uint8_t data[];      // array of entries #TODO: type for entries
} __attribute__ ((__packed__)) multiboot2_info_elf_sections_tag;
#define MULTIBOOT2_INFO_ELF_SECTIONS 9

typedef struct { // bios thing, dont care for now
    uint32_t type; // 10
    uint32_t size; 
    uint16_t version;
    uint16_t cseg;
    uint32_t offset;
    uint16_t cseg_16;
    uint16_t dseg;
    uint16_t flags;
    uint16_t cseg_len;
    uint16_t cseg_16_len;
    uint16_t dseg_len;
} __attribute__ ((__packed__)) multiboot2_info_apm_table_tag;
#define MULTIBOOT2_INFO_APM_TABLE 10

typedef struct {
    uint32_t type; // 11
    uint32_t size; 
    uint32_t pointer; // physical address of the efi system table
} __attribute__ ((__packed__)) multiboot2_info_efi_system_table_tag;
#define MULTIBOOT2_INFO_EFI_SYSTEM_TABLE 11

typedef struct {
    uint32_t type; // 12
    uint32_t size; 
    uint64_t pointer; // physical address of the efi system table
} __attribute__ ((__packed__)) multiboot2_info_efi64_system_table_tag;
#define MULTIBOOT2_INFO_EFI64_SYSTEM_TABLE 12

typedef struct { // bios thing, dont care for now
    uint32_t type; // 13
    uint32_t size; 
    uint8_t major;
    uint8_t minor;
    uint8_t reserved[6];
    uint8_t tables[];
} __attribute__ ((__packed__)) multiboot2_info_smbios_tag;
#define MULTIBOOT2_INFO_SMBIOS 13

typedef struct { // old acpi, dont care for now
    uint32_t type; // 14
    uint32_t size; 
    rsdp_v1_desc table; // refer to RSDP TABLES below
} __attribute__ ((__packed__)) multiboot2_info_acpi1_tag;
#define MULTIBOOT2_INFO_ACPI1 14

typedef struct { 
    uint32_t type; // 15
    uint32_t size; 
    rsdp_v2_desc table; // refer to RSDP TABLES below
} __attribute__ ((__packed__)) multiboot2_info_acpi2_tag;
#define MULTIBOOT2_INFO_ACPI2 15

typedef struct { // unused for now
    uint32_t type; // 16
    uint32_t size; 
    uint8_t netdata[];
} __attribute__ ((__packed__)) multiboot2_info_network_tag;
#define MULTIBOOT2_INFO_NETWORK 16

typedef struct {
    uint32_t type; // 17
    uint32_t size; 
    uint32_t desc_size; // size of one entry
    uint32_t desc_version; // 0
    uint8_t data[]; // array of entries #TODO: type for entries
} __attribute__ ((__packed__)) multiboot2_info_efi_memmap_tag;
#define MULTIBOOT2_INFO_EFI_MEMMAP 17

typedef struct {
    uint32_t type; // 18
    uint32_t size;
} __attribute__ ((__packed__)) multiboot2_info_bootservices_active_tag;
#define MULTIBOOT2_INFO_BOOTSERVICES_ACTIVE 18

typedef struct {
    uint32_t type; // 19
    uint32_t size;
    uint32_t pointer; // physical address of the efi image handle
} __attribute__ ((__packed__)) multiboot2_info_efi_image_tag;
#define MULTIBOOT2_INFO_EFI_IMAGE 19

typedef struct {
    uint32_t type; // 20
    uint32_t size;
    uint64_t pointer; // physical address of the efi image handle
} __attribute__ ((__packed__)) multiboot2_info_efi64_image_tag;
#define MULTIBOOT2_INFO_EFI64_IMAGE 20

typedef struct {
    uint32_t type; // 21
    uint32_t size;
    uint32_t load_base_addr; // used if image has relocatable header 
} __attribute__ ((__packed__)) multiboot2_info_image_base_tag;
#define MULTIBOOT2_INFO_IMAGE_BASE 21

// =================================================================================================
// MULTIBOOT2 ELF SECTIONS TAG
// =================================================================================================

// TODO: elf sections tag

// =================================================================================================
// MULTIBOOT2 MEMORY STRUCTURE
// =================================================================================================

typedef struct {
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
    uint32_t reserved;
} __attribute__ ((__packed__)) multiboot2_mmap_entry;

// =================================================================================================
// MULTIBOOT2 FRAMEBUFFER TAG
// =================================================================================================

typedef struct {
    uint32_t num_colors;
    framebuffer_palette palettes[];
} __attribute__ ((__packed__)) framebuffer_type_0;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} __attribute__ ((__packed__)) framebuffer_palette;

typedef struct {
    uint8_t red_field_position;
    uint8_t red_mask_size;
    uint8_t green_field_position;
    uint8_t green_mask_size;
    uint8_t blue_field_position;
    uint8_t blue_mask_size;
} __attribute__ ((__packed__)) framebuffer_type_1;

// =================================================================================================
// RSDP TABLES
// =================================================================================================

typedef struct {
    char signature[8];
    uint8_t checksum;
    char oem_id[6];
    uint8_t revision;
    uint32_t rsdt_addr;
} __attribute__ ((__packed__)) rsdp_v1_desc;

typedef struct {
    char signature[8];
    uint8_t checksum;
    char oem_id[6];
    uint8_t revision;
    uint32_t rsdt_addr;
    uint32_t length;
    uint64_t xsdt_addr;
    uint8_t extended_checksum;
    uint8_t reserved[3];
} __attribute__ ((__packed__)) rsdp_v2_desc;

#endif