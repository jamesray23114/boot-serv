/*********************************************************************
 * this file (efidef.h) is code adapted from the uefi specification, licensed under the BSD 2-Clause License
 * original source code available at https://uefi.org/sites/default/files/resources/UEFI_Spec_2_10_Aug29.pdf
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********************************************************************/

#pragma once

#include <typedef.h>

typedef uintn           EFI_STATUS;
typedef uint64          EFI_LBA;
typedef uintn           EFI_TPL;
typedef void*           EFI_HANDLE;
typedef void*           EFI_EVENT;

typedef struct {          
    uint32  Data1;
    uint16  Data2;
    uint16  Data3;
    byte    Data4[8]; 
}  EFI_GUID;

typedef struct {          
    uint16      Year;       // 1998 - 20XX
    byte        Month;      // 1 - 12
    byte        Day;        // 1 - 31
    byte        Hour;       // 0 - 23
    byte        Minute;     // 0 - 59
    byte        Second;     // 0 - 59
    byte        Pad1;
    uint32      Nanosecond; // 0 - 999,999,999
    int16       TimeZone;   // -1440 to 1440 or 2047
    byte        Daylight;
    byte        Pad2;
} EFI_TIME;

typedef uintn          EFI_PHYSICAL_ADDRESS;
typedef uintn          EFI_VIRTUAL_ADDRESS;

typedef enum {
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef struct {
    uint32                          Type;           
    uint32                          Pad;
    EFI_PHYSICAL_ADDRESS            PhysicalStart;  
    EFI_VIRTUAL_ADDRESS             VirtualStart;   
    uint64                          NumberOfPages;  
    uint64                          Attribute;      
} __attribute__((packed)) EFI_MEMORY_DESCRIPTOR;

typedef struct _EFI_DEVICE_PATH_PROTOCOL {
        byte                           Type;
        byte                           SubType;
        byte                           Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef EFI_DEVICE_PATH_PROTOCOL EFI_DEVICE_PATH;