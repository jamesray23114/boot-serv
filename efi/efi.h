#pragma once

#include "efiapi.h"
#include "efiprot.h"

extern EFI_SYSTEM_TABLE*   ST;
extern EFI_BOOT_SERVICES*  BS;

static inline bool guid_equal(EFI_GUID a, EFI_GUID b)
{
    if(a.Data1 != b.Data1) return false;
    if(a.Data2 != b.Data2) return false;
    if(a.Data3 != b.Data3) return false;
    if(a.Data4[0] != b.Data4[0]) return false;
    if(a.Data4[1] != b.Data4[1]) return false;
    if(a.Data4[2] != b.Data4[2]) return false;
    if(a.Data4[3] != b.Data4[3]) return false;
    if(a.Data4[4] != b.Data4[4]) return false;
    if(a.Data4[5] != b.Data4[5]) return false;
    if(a.Data4[6] != b.Data4[6]) return false;
    if(a.Data4[7] != b.Data4[7]) return false;
    return true;
}