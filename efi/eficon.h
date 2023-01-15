/*********************************************************************
 * this file (eficon.h) is code adapted from the uefi specification, licensed under the BSD 2-Clause License
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

#include <efidef.h>
#include <typedef.h>

struct _SIMPLE_TEXT_OUTPUT_INTERFACE;
struct _SIMPLE_INPUT_INTERFACE;

typedef EFI_STATUS (*EFI_TEXT_RESET) (
    struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
    bool                      ExtendedVerification
    );

typedef EFI_STATUS (*EFI_TEXT_OUTPUT_STRING) (
   struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
   uint16                       *String
    );

typedef EFI_STATUS (*EFI_TEXT_TEST_STRING) (
   struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
   uint16                       *String
    );

typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE) (
   struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
   uintn                        ModeNumber,
   uintn                       *Columns,
   uintn                       *Rows
    );

typedef EFI_STATUS (*EFI_TEXT_SET_MODE) (
   struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
   uintn                        ModeNumber
    );

typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE) (
   struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
   uintn                        Attribute
    );

typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN) (
   struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This
    );

typedef EFI_STATUS (*EFI_TEXT_SET_CURSOR_POSITION) (
   struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
   uintn                        Column,
   uintn                        Row
    );

typedef EFI_STATUS (*EFI_TEXT_ENABLE_CURSOR) (
   struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
   bool                      Enable
    );

typedef struct {
    int32
                               MaxMode;
    // current settings
    int32
                               Mode;
    int32
                               Attribute;
    int32
                               CursorColumn;
    int32
                               CursorRow;
    bool                         CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef struct _SIMPLE_TEXT_OUTPUT_INTERFACE {
    EFI_TEXT_RESET                  Reset;

    EFI_TEXT_OUTPUT_STRING          OutputString;
    EFI_TEXT_TEST_STRING            TestString;

    EFI_TEXT_QUERY_MODE             QueryMode;
    EFI_TEXT_SET_MODE               SetMode;
    EFI_TEXT_SET_ATTRIBUTE          SetAttribute;

    EFI_TEXT_CLEAR_SCREEN           ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION    SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR          EnableCursor;

    // Current mode
    SIMPLE_TEXT_OUTPUT_MODE         *Mode;
} SIMPLE_TEXT_OUTPUT_INTERFACE, EFI_SIMPLE_TEXT_OUT_PROTOCOL;

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
    { 0x387477c1, 0x69c7, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID


typedef struct {
    uint16                              ScanCode;
    uint16                              UnicodeChar;
} EFI_INPUT_KEY;

typedef EFI_STATUS (*EFI_INPUT_RESET) (
   struct _SIMPLE_INPUT_INTERFACE   *This,
   bool                          ExtendedVerification
    );

typedef EFI_STATUS (*EFI_INPUT_READ_KEY) (
   struct _SIMPLE_INPUT_INTERFACE   *This,
   EFI_INPUT_KEY                   *Key
    );

typedef struct _SIMPLE_INPUT_INTERFACE {
    EFI_INPUT_RESET                     Reset;
    EFI_INPUT_READ_KEY                  ReadKeyStroke;
    EFI_EVENT                           WaitForKey;
} SIMPLE_INPUT_INTERFACE, EFI_SIMPLE_TEXT_IN_PROTOCOL;


