#include <efi.h>
#include <efiapi.h>
#include <eficon.h>
#include <efidef.h>
#include <efiprot.h>

void efi_main(EFI_HANDLE* ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    EFI_SYSTEM_TABLE*  ST = SystemTable;
    EFI_BOOT_SERVICES* BS = ST->BootServices;
    
    SIMPLE_TEXT_OUTPUT_INTERFACE* COUT = ST->ConOut;

    BS->SetWatchdogTimer(0, 0, 0, null);
    COUT->ClearScreen(COUT);
    COUT->OutputString(COUT, L"Hello, world!");
    
    

    while (true) ;
}