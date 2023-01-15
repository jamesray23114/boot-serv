/*********************************************************************
 * this file (efiprot.h) is code adapted from the uefi specification, licensed under the BSD 2-Clause License
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

#define EFI_SUCCESS                     0 
#define STR_EFI_SUCCESS                 L"Success"

#define EFI_LOAD_ERROR                  1 | 0x8000000000000000
#define STR_EFI_LOAD_ERROR              L"Load Error"

#define EFI_INVALID_PARAMETER           2 | 0x8000000000000000
#define STR_EFI_INVALID_PARAMETER       L"Invalid Parameter"

#define EFI_UNSUPPORTED                 3 | 0x8000000000000000
#define STR_EFI_UNSUPPORTED             L"Unsupported"

#define EFI_BAD_BUFFER_SIZE             4 | 0x8000000000000000
#define STR_EFI_BAD_BUFFER_SIZE         L"Bad Buffer Size"

#define EFI_BUFFER_TOO_SMALL            5 | 0x8000000000000000
#define STR_EFI_BUFFER_TOO_SMALL        L"Buffer Too Small"

#define EFI_NOT_READY                   6 | 0x8000000000000000
#define STR_EFI_NOT_READY               L"Not Ready"

#define EFI_DEVICE_ERROR                7 | 0x8000000000000000
#define STR_EFI_DEVICE_ERROR            L"Device Error"

#define EFI_WRITE_PROTECTED             8 | 0x8000000000000000
#define STR_EFI_WRITE_PROTECTED         L"Write Protected"

#define EFI_OUT_OF_RESOURCES            9 | 0x8000000000000000
#define STR_EFI_OUT_OF_RESOURCES        L"Out of Resources"

#define EFI_VOLUME_CORRUPTED            10 | 0x00000000
#define STR_EFI_VOLUME_CORRUPTED        L"Volume Corrupted"

#define EFI_VOLUME_FULL                 11 | 0x8000000000000000
#define STR_EFI_VOLUME_FULL             L"Volume Full"

#define EFI_NO_MEDIA                    12 | 0x8000000000000000
#define STR_EFI_NO_MEDIA                L"No Media"

#define EFI_MEDIA_CHANGED               13 | 0x8000000000000000
#define STR_EFI_MEDIA_CHANGED           L"Media Changed"

#define EFI_NOT_FOUND                   14 | 0x8000000000000000
#define STR_EFI_NOT_FOUND               L"Not Found"

#define EFI_ACCESS_DENIED               15 | 0x8000000000000000
#define STR_EFI_ACCESS_DENIED           L"Access Denied"

#define EFI_NO_RESPONSE                 16 | 0x8000000000000000
#define STR_EFI_NO_RESPONSE             L"No Response"

#define EFI_NO_MAPPING                  17 | 0x8000000000000000
#define STR_EFI_NO_MAPPING              L"No Mapping"

#define EFI_TIMEOUT                     18 | 0x8000000000000000
#define STR_EFI_TIMEOUT                 L"Time Out"

#define EFI_NOT_STARTED                 19 | 0x8000000000000000
#define STR_EFI_NOT_STARTED             L"Not Started"

#define EFI_ALREADY_STARTED             20 | 0x8000000000000000
#define STR_EFI_ALREADY_STARTED         L"Already Started"

#define EFI_ABORTED                     21 | 0x8000000000000000
#define STR_EFI_ABORTED                 L"Aborted"

#define EFI_ICMP_ERROR                  22 | 0x8000000000000000
#define STR_EFI_ICMP_ERROR              L"ICMP Error"

#define EFI_TFTP_ERROR                  23 | 0x8000000000000000
#define STR_EFI_TFTP_ERROR              L"TFTP Error"

#define EFI_PROTOCOL_ERROR              24 | 0x8000000000000000
#define STR_EFI_PROTOCOL_ERROR          L"Protocol Error"

#define EFI_INCOMPATIBLE_VER            25 | 0x8000000000000000
#define STR_EFI_INCOMPATIBLE_VER        L"Incompatible Version"

#define EFI_SECURITY_VIOLATION          26 | 0x8000000000000000
#define STR_EFI_SECURITY_VIOLATION      L"Security Violation"

#define EFI_CRC_ERROR                   27 | 0x8000000000000000
#define STR_EFI_CRC_ERROR               L"CRC Error" 

#define EFI_END_OF_MEDIA                28 | 0x8000000000000000
#define STR_EFI_END_OF_MEDIA            L"End of Media"

#define EFI_END_OF_FILE                 31 | 0x8000000000000000
#define STR_EFI_END_OF_FILE             L"End of File"

#define EFI_INVALID_LANGUAGE            32 | 0x8000000000000000
#define STR_EFI_INVALID_LANGUAGE        L"Invalid Language"

#define EFI_COMPROMISED_DATA            33 | 0x8000000000000000
#define STR_EFI_COMPROMISED_DATA        L"Compromised Data"

#define EFI_IP_ADDRESS_CONFLICT         34 | 0x8000000000000000
#define STR_EFI_IP_ADDRESS_CONFLICT     L"IP Address Conflict"

#define EFI_HTTP_ERROR                  35 | 0x8000000000000000
#define STR_EFI_HTTP_ERROR              L"HTTP Error"

#define EFI_WARN_UNKNOWN_GLYPH          1 | 0x00000000
#define STR_EFI_WARN_UNKNOWN_GLYPH      L"Unknown Glyph"

#define EFI_WARN_DELETE_FAILURE         2 | 0x00000000
#define STR_EFI_WARN_DELETE_FAILURE     L"Delete Failure"

#define EFI_WARN_WRITE_FAILURE          3 | 0x00000000
#define STR_EFI_WARN_WRITE_FAILURE      L"Write Failure"

#define EFI_WARN_BUFFER_TOO_SMALL       4 | 0x00000000
#define STR_EFI_WARN_BUFFER_TOO_SMALL   L"Buffer Too Small" 

#define EFI_WARN_STALE_DATA             5 | 0x00000000
#define STR_EFI_WARN_STALE_DATA         L"Stale Data"

#define EFI_WARN_FILE_SYSTEM            6 | 0x00000000
#define STR_EFI_WARN_FILE_SYSTEM        L"File System"

#define EFI_WARN_RESET_REQUIRED         7 | 0x00000000
#define STR_EFI_WARN_RESET_REQUIRED     L"Reset Required"

uint16_t* status_to_string(uintn status) {
    switch (status) {
        case EFI_SUCCESS:               return STR_EFI_SUCCESS;
        case EFI_LOAD_ERROR:            return STR_EFI_LOAD_ERROR;
        case EFI_INVALID_PARAMETER:     return STR_EFI_INVALID_PARAMETER;
        case EFI_UNSUPPORTED:           return STR_EFI_UNSUPPORTED;
        case EFI_BAD_BUFFER_SIZE:       return STR_EFI_BAD_BUFFER_SIZE;
        case EFI_BUFFER_TOO_SMALL:      return STR_EFI_BUFFER_TOO_SMALL;
        case EFI_NOT_READY:             return STR_EFI_NOT_READY;
        case EFI_DEVICE_ERROR:          return STR_EFI_DEVICE_ERROR;
        case EFI_WRITE_PROTECTED:       return STR_EFI_WRITE_PROTECTED;
        case EFI_OUT_OF_RESOURCES:      return STR_EFI_OUT_OF_RESOURCES;
        case EFI_VOLUME_CORRUPTED:      return STR_EFI_VOLUME_CORRUPTED;
        case EFI_VOLUME_FULL:           return STR_EFI_VOLUME_FULL;
        case EFI_NO_MEDIA:              return STR_EFI_NO_MEDIA;
        case EFI_MEDIA_CHANGED:         return STR_EFI_MEDIA_CHANGED;
        case EFI_NOT_FOUND:             return STR_EFI_NOT_FOUND;
        case EFI_ACCESS_DENIED:         return STR_EFI_ACCESS_DENIED;
        case EFI_NO_RESPONSE:           return STR_EFI_NO_RESPONSE;
        case EFI_NO_MAPPING:            return STR_EFI_NO_MAPPING;
        case EFI_TIMEOUT:               return STR_EFI_TIMEOUT;
        case EFI_NOT_STARTED:           return STR_EFI_NOT_STARTED;
        case EFI_ALREADY_STARTED:       return STR_EFI_ALREADY_STARTED;
        case EFI_ABORTED:               return STR_EFI_ABORTED;
        case EFI_ICMP_ERROR:            return STR_EFI_ICMP_ERROR;
        case EFI_TFTP_ERROR:            return STR_EFI_TFTP_ERROR;
        case EFI_PROTOCOL_ERROR:        return STR_EFI_PROTOCOL_ERROR;
        case EFI_INCOMPATIBLE_VER:      return STR_EFI_INCOMPATIBLE_VER;
        case EFI_SECURITY_VIOLATION:    return STR_EFI_SECURITY_VIOLATION;
        case EFI_CRC_ERROR:             return STR_EFI_CRC_ERROR;
        case EFI_END_OF_MEDIA:          return STR_EFI_END_OF_MEDIA;
        case EFI_END_OF_FILE:           return STR_EFI_END_OF_FILE;
        case EFI_INVALID_LANGUAGE:      return STR_EFI_INVALID_LANGUAGE;
        case EFI_COMPROMISED_DATA:      return STR_EFI_COMPROMISED_DATA;
        case EFI_IP_ADDRESS_CONFLICT:   return STR_EFI_IP_ADDRESS_CONFLICT;
        case EFI_HTTP_ERROR:            return STR_EFI_HTTP_ERROR;
        case EFI_WARN_UNKNOWN_GLYPH:    return STR_EFI_WARN_UNKNOWN_GLYPH;
        case EFI_WARN_DELETE_FAILURE:   return STR_EFI_WARN_DELETE_FAILURE;
        case EFI_WARN_WRITE_FAILURE:    return STR_EFI_WARN_WRITE_FAILURE;
        case EFI_WARN_BUFFER_TOO_SMALL: return STR_EFI_WARN_BUFFER_TOO_SMALL;
        case EFI_WARN_STALE_DATA:       return STR_EFI_WARN_STALE_DATA;
        case EFI_WARN_FILE_SYSTEM:      return STR_EFI_WARN_FILE_SYSTEM;
        case EFI_WARN_RESET_REQUIRED:   return STR_EFI_WARN_RESET_REQUIRED;

        default:    
            return  L"Unknown Error";
    }
}