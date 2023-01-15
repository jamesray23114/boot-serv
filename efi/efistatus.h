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

#define EFI_SUCCESS                 0 
#define STR_EFI_SUCCESS             "Success"

#define EFI_LOAD_ERROR              1 | 0x80000000
#define STR_EFI_LOAD_ERROR          "Load Error"

#define EFI_INVALID_PARAMETER       2 | 0x80000000
#define STR_EFI_INVALID_PARAMETER   "Invalid Parameter"

#define EFI_UNSUPPORTED             3 | 0x80000000
#define STR_EFI_UNSUPPORTED         "Unsupported"

#define EFI_BAD_BUFFER_SIZE         4 | 0x80000000
#define STR_EFI_BAD_BUFFER_SIZE     "Bad Buffer Size"

#define EFI_BUFFER_TOO_SMALL        5 | 0x80000000
#define STR_EFI_BUFFER_TOO_SMALL    "Buffer Too Small"

#define EFI_NOT_READY               6 | 0x80000000
#define STR_EFI_NOT_READY           "Not Ready"

#define EFI_DEVICE_ERROR            7 | 0x80000000
#define STR_EFI_DEVICE_ERROR        "Device Error"

#define EFI_WRITE_PROTECTED         8 | 0x80000000
#define STR_EFI_WRITE_PROTECTED     "Write Protected"

#define EFI_OUT_OF_RESOURCES        9 | 0x80000000
#define STR_EFI_OUT_OF_RESOURCES    "Out of Resources"

#define EFI_VOLUME_CORRUPTED        10 | 0x00000000
#define STR_EFI_VOLUME_CORRUPTED    "Volume Corrupted"

#define EFI_VOLUME_FULL             11 | 0x80000000
#define STR_EFI_VOLUME_FULL         "Volume Full"

#define EFI_NO_MEDIA                12 | 0x80000000
#define STR_EFI_NO_MEDIA            "No Media"

#define EFI_MEDIA_CHANGED           13 | 0x80000000
#define STR_EFI_MEDIA_CHANGED       "Media Changed"

#define EFI_NOT_FOUND               14 | 0x80000000
#define STR_EFI_NOT_FOUND           "Not Found"

#define EFI_ACCESS_DENIED           15 | 0x80000000
#define STR_EFI_ACCESS_DENIED       "Access Denied"

#define EFI_NO_RESPONSE             16 | 0x80000000
#define STR_EFI_NO_RESPONSE         "No Response"

#define EFI_NO_MAPPING              17 | 0x80000000
#define STR_EFI_NO_MAPPING          "No Mapping"

#define EFI_TIMEOUT                 18 | 0x80000000
#define STR_EFI_TIMEOUT             "Time Out"

#define EFI_NOT_STARTED             19 | 0x80000000
#define STR_EFI_NOT_STARTED         "Not Started"

#define EFI_ALREADY_STARTED         20 | 0x80000000
#define STR_EFI_ALREADY_STARTED     "Already Started"

#define EFI_ABORTED                 21 | 0x80000000
#define STR_EFI_ABORTED             "Aborted"

#define EFI_ICMP_ERROR              22 | 0x80000000
#define STR_EFI_ICMP_ERROR          "ICMP Error"

#define EFI_TFTP_ERROR              23 | 0x80000000
#define STR_EFI_TFTP_ERROR          "TFTP Error"

#define EFI_PROTOCOL_ERROR          24 | 0x80000000
#define STR_EFI_PROTOCOL_ERROR      "Protocol Error"

#define EFI_INCOMPATIBLE_VERSION    25 | 0x80000000
#define STR_EFI_INCOMPATIBLE_VERSION "Incompatible Version"

#define EFI_SECURITY_VIOLATION      26 | 0x80000000
#define STR_EFI_SECURITY_VIOLATION  "Security Violation"

#define EFI_CRC_ERROR               27 | 0x80000000
#define STR_EFI_CRC_ERROR           "CRC Error" 

#define EFI_END_OF_MEDIA            28 | 0x80000000
#define STR_EFI_END_OF_MEDIA        "End of Media"

#define EFI_END_OF_FILE             31 | 0x80000000
#define STR_EFI_END_OF_FILE         "End of File"

#define EFI_INVALID_LANGUAGE        32 | 0x80000000
#define STR_EFI_INVALID_LANGUAGE    "Invalid Language"

#define EFI_COMPROMISED_DATA        33 | 0x80000000
#define STR_EFI_COMPROMISED_DATA    "Compromised Data"

#define EFI_IP_ADDRESS_CONFLICT     34 | 0x80000000
#define STR_EFI_IP_ADDRESS_CONFLICT "IP Address Conflict"

#define EFI_HTTP_ERROR              35 | 0x80000000
#define STR_EFI_HTTP_ERROR          "HTTP Error"

#define EFI_UNKNOWN_GLYPH           1 
#define STR_EFI_UNKNOWN_GLYPH       "Unknown Glyph"

#define EFI_DELETE_FAILURE          2 
#define STR_EFI_DELETE_FAILURE      "Delete Failure"

#define EFI_WRITE_FAILURE           3
#define STR_EFI_WRITE_FAILURE       "Write Failure"

#define EFI_BUFFER_TOO_SMALL        4
#define STR_EFI_BUFFER_TOO_SMALL    "Buffer Too Small"

#define EFI_STALE_DATA              5
#define STR_EFI_STALE_DATA          "Stale Data"

#define EFI_VOLUME_CORRUPTED        6
#define STR_EFI_VOLUME_CORRUPTED    "Volume Corrupted"

#define EFI_RESET_REQUIRED          7
#define STR_EFI_RESET_REQUIRED      "Reset Required"


