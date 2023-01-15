/*********************************************************************
 * this file (efi.h) is code adapted from the uefi specification, licensed under the BSD 2-Clause License
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

#include <efiapi.h>
#include <efiprot.h>
#include <efistatus.h>

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