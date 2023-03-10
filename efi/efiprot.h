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

#include "efidef.h"

#define INTERFACE_DECL(prot) struct prot

//
// Block IO protocol
//

#define EFI_BLOCK_IO_PROTOCOL_GUID \
    { 0x964e5b21, 0x6459, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define BLOCK_IO_PROTOCOL EFI_BLOCK_IO_PROTOCOL_GUID

#define EFI_BLOCK_IO_PROTOCOL_REVISION    0x00010000
#define EFI_BLOCK_IO_PROTOCOL_REVISION2   0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3   ((2<<16) | 31)
#define EFI_BLOCK_IO_INTERFACE_REVISION   EFI_BLOCK_IO_PROTOCOL_REVISION
#define EFI_BLOCK_IO_INTERFACE_REVISION2  EFI_BLOCK_IO_PROTOCOL_REVISION2
#define EFI_BLOCK_IO_INTERFACE_REVISION3  EFI_BLOCK_IO_PROTOCOL_REVISION3

INTERFACE_DECL(_EFI_BLOCK_IO_PROTOCOL);

typedef EFI_STATUS (*EFI_BLOCK_RESET) (
   struct _EFI_BLOCK_IO_PROTOCOL  *This,
   bool                        ExtendedVerification
    );

typedef uintn ( *EFI_BLOCK_READ) (
   struct _EFI_BLOCK_IO_PROTOCOL  *This,
   uint32                         MediaId,
   EFI_LBA                        LBA,
   uintn                          BufferSize,
  void                         *Buffer
    );


typedef uintn ( *EFI_BLOCK_WRITE) (
   struct _EFI_BLOCK_IO_PROTOCOL  *This,
   uint32                         MediaId,
   EFI_LBA                        LBA,
   uintn                          BufferSize,
  void                          *Buffer
    );


typedef uintn ( *EFI_BLOCK_FLUSH) (
   struct _EFI_BLOCK_IO_PROTOCOL  *This
    );



typedef struct {
    uint32              MediaId;
    bool             RemovableMedia;
    bool             MediaPresent;

    bool             LogicalPartition;
    bool             ReadOnly;
    bool             WriteCaching;

    uint32              BlockSize;
    uint32              IoAlign;

    EFI_LBA             LastBlock;

    /* revision 2 */
    EFI_LBA             LowestAlignedLba;
    uint32              LogicalBlocksPerPhysicalBlock;
    /* revision 3 */
    uint32              OptimalTransferLengthGranularity;
} EFI_BLOCK_IO_MEDIA;

typedef struct _EFI_BLOCK_IO_PROTOCOL {
    uint64                  Revision;

    EFI_BLOCK_IO_MEDIA      *Media;

    EFI_BLOCK_RESET         Reset;
    EFI_BLOCK_READ          ReadBlocks;
    EFI_BLOCK_WRITE         WriteBlocks;
    EFI_BLOCK_FLUSH         FlushBlocks;

} EFI_BLOCK_IO_PROTOCOL;

typedef struct _EFI_BLOCK_IO_PROTOCOL _EFI_BLOCK_IO;
typedef EFI_BLOCK_IO_PROTOCOL EFI_BLOCK_IO;

#define EFI_BLOCK_IO2_PROTOCOL_GUID \
    { 0xa77b2472, 0xe282, 0x4e9f, {0xa2, 0x45, 0xc2, 0xc0, 0xe2, 0x7b, 0xbc, 0xc1} }

INTERFACE_DECL(_EFI_BLOCK_IO2_PROTOCOL);

typedef struct {
    EFI_EVENT               Event;
    uintn              TransactionStatus;
} EFI_BLOCK_IO2_TOKEN;

typedef uintn ( *EFI_BLOCK_RESET_EX) (
   struct _EFI_BLOCK_IO2_PROTOCOL  *This,
   bool                         ExtendedVerification
    );

typedef uintn ( *EFI_BLOCK_READ_EX) (
   struct _EFI_BLOCK_IO2_PROTOCOL  *This,
   uint32                          MediaId,
   EFI_LBA                         LBA,
  EFI_BLOCK_IO2_TOKEN         *Token,
   uintn                           BufferSize,
  void                          *Buffer
    );

typedef uintn ( *EFI_BLOCK_WRITE_EX) (
   struct _EFI_BLOCK_IO2_PROTOCOL  *This,
   uint32                          MediaId,
   EFI_LBA                         LBA,
  EFI_BLOCK_IO2_TOKEN         *Token,
   uintn                           BufferSize,
  void                           *Buffer
    );

typedef uintn ( *EFI_BLOCK_FLUSH_EX) (
   struct _EFI_BLOCK_IO2_PROTOCOL  *This,
  EFI_BLOCK_IO2_TOKEN         *Token
    );

typedef struct _EFI_BLOCK_IO2_PROTOCOL {
    EFI_BLOCK_IO_MEDIA  *Media;
    EFI_BLOCK_RESET_EX  Reset;
    EFI_BLOCK_READ_EX   ReadBlocksEx;
    EFI_BLOCK_WRITE_EX  WriteBlocksEx;
    EFI_BLOCK_FLUSH_EX  FlushBlocksEx;
} EFI_BLOCK_IO2_PROTOCOL;

//
// Disk Block IO protocol
//

#define EFI_DISK_IO_PROTOCOL_GUID \
    { 0xce345171, 0xba0b, 0x11d2,  {0x8e, 0x4f, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define DISK_IO_PROTOCOL EFI_DISK_IO_PROTOCOL_GUID

#define EFI_DISK_IO_PROTOCOL_REVISION  0x00010000
#define EFI_DISK_IO_INTERFACE_REVISION EFI_DISK_IO_PROTOCOL_REVISION

INTERFACE_DECL(_EFI_DISK_IO_PROTOCOL);

typedef uintn ( *EFI_DISK_READ) (
   struct _EFI_DISK_IO_PROTOCOL  *This,
   uint32                        MediaId,
   uint64                        Offset,
   uintn                         BufferSize,
  void                        *Buffer
    );


typedef uintn ( *EFI_DISK_WRITE) (
   struct _EFI_DISK_IO_PROTOCOL  *This,
   uint32                        MediaId,
   uint64                        Offset,
   uintn                         BufferSize,
  void                         *Buffer
    );


typedef struct _EFI_DISK_IO_PROTOCOL {
    uint64              Revision;
    EFI_DISK_READ       ReadDisk;
    EFI_DISK_WRITE      WriteDisk;
} EFI_DISK_IO_PROTOCOL;

typedef struct _EFI_DISK_IO_PROTOCOL _EFI_DISK_IO;
typedef EFI_DISK_IO_PROTOCOL EFI_DISK_IO;


#define EFI_DISK_IO2_PROTOCOL_GUID \
    { 0x151c8eae, 0x7f2c, 0x472c,  {0x9e, 0x54, 0x98, 0x28, 0x19, 0x4f, 0x6a, 0x88} }

#define EFI_DISK_IO2_PROTOCOL_REVISION  0x00020000

INTERFACE_DECL(_EFI_DISK_IO2_PROTOCOL);

typedef struct {
    EFI_EVENT  Event;
    uintn TransactionStatus;
} EFI_DISK_IO2_TOKEN;

typedef uintn ( *EFI_DISK_CANCEL_EX) (
   struct _EFI_DISK_IO2_PROTOCOL  *This
    );

typedef uintn ( *EFI_DISK_READ_EX) (
   struct _EFI_DISK_IO2_PROTOCOL  *This,
   uint32                         MediaId,
   uint64                         Offset,
  EFI_DISK_IO2_TOKEN         *Token,
   uintn                          BufferSize,
  void                         *Buffer
    );

typedef uintn ( *EFI_DISK_WRITE_EX) (
   struct _EFI_DISK_IO2_PROTOCOL  *This,
   uint32                         MediaId,
   uint64                         Offset,
  EFI_DISK_IO2_TOKEN         *Token,
   uintn                          BufferSize,
  void                          *Buffer
    );

typedef uintn ( *EFI_DISK_FLUSH_EX) (
   struct _EFI_DISK_IO2_PROTOCOL  *This,
  EFI_DISK_IO2_TOKEN         *Token
    );

typedef struct _EFI_DISK_IO2_PROTOCOL {
    uint64                            Revision;
    EFI_DISK_CANCEL_EX                Cancel;
    EFI_DISK_READ_EX                  ReadDiskEx;
    EFI_DISK_WRITE_EX                 WriteDiskEx;
    EFI_DISK_FLUSH_EX                 FlushDiskEx;
} EFI_DISK_IO2_PROTOCOL;

//
// Simple file system protocol
//

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
    { 0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID

INTERFACE_DECL(_EFI_SIMPLE_FILE_SYSTEM_PROTOCOL);
INTERFACE_DECL(_EFI_FILE_HANDLE);

typedef uintn ( *EFI_VOLUME_OPEN) (
   struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL    *This,
   struct _EFI_FILE_HANDLE                   **Root
    );

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION  0x00010000
#define EFI_FILE_IO_INTERFACE_REVISION EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    uint64                  Revision;
    EFI_VOLUME_OPEN         OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL _EFI_FILE_IO_INTERFACE;
typedef EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_FILE_IO_INTERFACE;

//
//
//

typedef uintn ( *EFI_FILE_OPEN) (
   struct _EFI_FILE_HANDLE  *File,
   struct _EFI_FILE_HANDLE **NewHandle,
   uint16                   *FileName,
   uint64                   OpenMode,
   uint64                   Attributes
    );

// Open modes
#define EFI_FILE_MODE_READ      0x0000000000000001
#define EFI_FILE_MODE_WRITE     0x0000000000000002
#define EFI_FILE_MODE_CREATE    0x8000000000000000

// File attributes
#define EFI_FILE_READ_ONLY      0x0000000000000001
#define EFI_FILE_HIDDEN         0x0000000000000002
#define EFI_FILE_SYSTEM         0x0000000000000004
#define EFI_FILE_RESERVIED      0x0000000000000008
#define EFI_FILE_DIRECTORY      0x0000000000000010
#define EFI_FILE_ARCHIVE        0x0000000000000020
#define EFI_FILE_VALID_ATTR     0x0000000000000037

typedef uintn ( *EFI_FILE_CLOSE) (
   struct _EFI_FILE_HANDLE  *File
    );

typedef uintn ( *EFI_FILE_DELETE) (
   struct _EFI_FILE_HANDLE  *File
    );

typedef uintn ( *EFI_FILE_READ) (
   struct _EFI_FILE_HANDLE  *File,
  uintn                *BufferSize,
  void                   *Buffer
    );

typedef uintn ( *EFI_FILE_WRITE) (
   struct _EFI_FILE_HANDLE  *File,
  uintn                *BufferSize,
  void                    *Buffer
    );

typedef uintn ( *EFI_FILE_SET_POSITION) (
   struct _EFI_FILE_HANDLE  *File,
   uint64                   Position
    );

typedef uintn ( *EFI_FILE_GET_POSITION) (
   struct _EFI_FILE_HANDLE  *File,
   uint64                  *Position
    );

typedef uintn ( *EFI_FILE_GET_INFO) (
   struct _EFI_FILE_HANDLE  *File,
   EFI_GUID                 *InformationType,
  uintn                *BufferSize,
  void                   *Buffer
    );

typedef uintn ( *EFI_FILE_SET_INFO) (
   struct _EFI_FILE_HANDLE  *File,
   EFI_GUID                 *InformationType,
   uintn                    BufferSize,
  void                    *Buffer
    );

typedef uintn ( *EFI_FILE_FLUSH) (
   struct _EFI_FILE_HANDLE  *File
    );

typedef struct {
    EFI_EVENT       Event;
    uintn      Status;
    uintn           BufferSize;
   void           *Buffer;
} EFI_FILE_IO_TOKEN;

typedef uintn ( *EFI_FILE_OPEN_EX)(
   struct _EFI_FILE_HANDLE  *File,
   struct _EFI_FILE_HANDLE **NewHandle,
   uint16                   *FileName,
   uint64                   OpenMode,
   uint64                   Attributes,
  EFI_FILE_IO_TOKEN    *Token
    );

typedef uintn ( *EFI_FILE_READ_EX) (
   struct _EFI_FILE_HANDLE  *File,
  EFI_FILE_IO_TOKEN    *Token
    );

typedef uintn ( *EFI_FILE_WRITE_EX) (
   struct _EFI_FILE_HANDLE  *File,
  EFI_FILE_IO_TOKEN    *Token
    );

typedef uintn ( *EFI_FILE_FLUSH_EX) (
   struct _EFI_FILE_HANDLE  *File,
  EFI_FILE_IO_TOKEN    *Token
    );

#define EFI_FILE_PROTOCOL_REVISION         0x00010000
#define EFI_FILE_PROTOCOL_REVISION2        0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION  EFI_FILE_PROTOCOL_REVISION2
#define EFI_FILE_HANDLE_REVISION           EFI_FILE_PROTOCOL_REVISION

typedef struct _EFI_FILE_HANDLE {
    uint64                  Revision;
    EFI_FILE_OPEN           Open;
    EFI_FILE_CLOSE          Close;
    EFI_FILE_DELETE         Delete;
    EFI_FILE_READ           Read;
    EFI_FILE_WRITE          Write;
    EFI_FILE_GET_POSITION   GetPosition;
    EFI_FILE_SET_POSITION   SetPosition;
    EFI_FILE_GET_INFO       GetInfo;
    EFI_FILE_SET_INFO       SetInfo;
    EFI_FILE_FLUSH          Flush;
    EFI_FILE_OPEN_EX        OpenEx;
    EFI_FILE_READ_EX        ReadEx;
    EFI_FILE_WRITE_EX       WriteEx;
    EFI_FILE_FLUSH_EX       FlushEx;
} EFI_FILE_PROTOCOL, *EFI_FILE_HANDLE;

typedef EFI_FILE_PROTOCOL EFI_FILE;


//
// File information types
//

#define EFI_FILE_INFO_ID   \
    { 0x9576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }

typedef struct {
    uint64                  Size;
    uint64                  FileSize;
    uint64                  PhysicalSize;
    EFI_TIME                CreateTime;
    EFI_TIME                LastAccessTime;
    EFI_TIME                ModificationTime;
    uint64                  Attribute;
    uint16                  FileName[1];
} EFI_FILE_INFO;

#define EFI_FILE_SYSTEM_INFO_ID    \
    { 0x9576e93, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }

typedef struct {
    uint64                  Size;
    bool                 ReadOnly;
    uint64                  VolumeSize;
    uint64                  FreeSpace;
    uint32                  BlockSize;
    uint16                  VolumeLabel[1];
} EFI_FILE_SYSTEM_INFO;

#define EFI_FILE_SYSTEM_VOLUME_LABEL_ID    \
    { 0xDB47D7D3,0xFE81, 0x11d3, {0x9A, 0x35, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D} }

typedef struct {
    uint16                  VolumeLabel[1];
} EFI_FILE_SYSTEM_VOLUME_LABEL;

#define SIZE_OF_EFI_FILE_SYSTEM_VOLUME_LABEL_INFO EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_VOLUME_LABEL,VolumeLabel)

//
// For compatibility with older versions of gnu-efi
//
#define EFI_FILE_SYSTEM_VOLUME_LABEL_INFO_ID EFI_FILE_SYSTEM_VOLUME_LABEL_ID
#define EFI_FILE_SYSTEM_VOLUME_LABEL_INFO    EFI_FILE_SYSTEM_VOLUME_LABEL

//
// Load file protocol
//


#define EFI_LOAD_FILE_PROTOCOL_GUID \
    { 0x56EC3091, 0x954C, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B} }
#define LOAD_FILE_PROTOCOL EFI_LOAD_FILE_PROTOCOL_GUID

INTERFACE_DECL(_EFI_LOAD_FILE_PROTOCOL);

typedef uintn ( *EFI_LOAD_FILE) (
   struct _EFI_LOAD_FILE_PROTOCOL  *This,
   EFI_DEVICE_PATH                  *FilePath,
   bool                          BootPolicy,
  uintn                        *BufferSize,
  void                            *Buffer
    );

typedef struct _EFI_LOAD_FILE_PROTOCOL {
    EFI_LOAD_FILE                       LoadFile;
} EFI_LOAD_FILE_PROTOCOL;

typedef struct _EFI_LOAD_FILE_PROTOCOL _EFI_LOAD_FILE_INTERFACE;
typedef EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE_INTERFACE;

//
// Device IO protocol
//

#define EFI_DEVICE_IO_PROTOCOL_GUID \
    { 0xaf6ac311, 0x84c3, 0x11d2, {0x8e, 0x3c, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define DEVICE_IO_PROTOCOL EFI_DEVICE_IO_PROTOCOL_GUID

INTERFACE_DECL(_EFI_DEVICE_IO_PROTOCOL);

typedef enum {
    IO_uint8,
    IO_UINT16,
    IO_uint32,
    IO_uint64,
//
// Specification Change: Copy from MMIO to MMIO vs. MMIO to buffer, buffer to MMIO
//
    MMIO_COPY_uint8,
    MMIO_COPY_UINT16,
    MMIO_COPY_uint32,
    MMIO_COPY_uint64
} EFI_IO_WIDTH;

#define EFI_PCI_ADDRESS(_bus,_dev,_func) \
    ( (uint64) ( (((uintn)_bus) << 24) + (((uintn)_dev) << 16) + (((uintn)_func) << 8) ) )


typedef uintn ( *EFI_DEVICE_IO) (
   struct _EFI_DEVICE_IO_PROTOCOL *This,
   EFI_IO_WIDTH                 Width,
   uint64                       Address,
   uintn                        Count,
   void                         *Buffer
    );

typedef struct {
    EFI_DEVICE_IO                   Read;
    EFI_DEVICE_IO                   Write;
} EFI_IO_ACCESS;

typedef uintn ( *EFI_PCI_DEVICE_PATH) (
   struct _EFI_DEVICE_IO_PROTOCOL   *This,
   uint64                           Address,
  EFI_DEVICE_PATH              **PciDevicePath
    );

typedef enum {
    EfiBusMasterRead,
    EfiBusMasterWrite,
    EfiBusMasterCommonBuffer
} EFI_IO_OPERATION_TYPE;

typedef uintn ( *EFI_IO_MAP) (
   struct _EFI_DEVICE_IO_PROTOCOL   *This,
   EFI_IO_OPERATION_TYPE            Operation,
   EFI_PHYSICAL_ADDRESS             *HostAddress,
  uintn                             *NumberOfBytes,
   EFI_PHYSICAL_ADDRESS             *DeviceAddress,
  void                              **Mapping
    );

typedef uintn ( *EFI_IO_UNMAP) (
   struct _EFI_DEVICE_IO_PROTOCOL   *This,
  void                            *Mapping
    );

typedef uintn ( *EFI_IO_ALLOCATE_BUFFER) (
   struct _EFI_DEVICE_IO_PROTOCOL   *This,
   EFI_ALLOCATE_TYPE                Type,
   EFI_MEMORY_TYPE                  MemoryType,
   uintn                            Pages,
  EFI_PHYSICAL_ADDRESS         *HostAddress
    );

typedef uintn ( *EFI_IO_FLUSH) (
   struct _EFI_DEVICE_IO_PROTOCOL   *This
    );

typedef uintn ( *EFI_IO_FREE_BUFFER) (
   struct _EFI_DEVICE_IO_PROTOCOL   *This,
   uintn                            Pages,
   EFI_PHYSICAL_ADDRESS             HostAddress
    );

typedef struct _EFI_DEVICE_IO_PROTOCOL {
    EFI_IO_ACCESS                       Mem;
    EFI_IO_ACCESS                       Io;
    EFI_IO_ACCESS                       Pci;
    EFI_IO_MAP                          Map;
    EFI_PCI_DEVICE_PATH                 PciDevicePath;
    EFI_IO_UNMAP                        Unmap;
    EFI_IO_ALLOCATE_BUFFER              AllocateBuffer;
    EFI_IO_FLUSH                        Flush;
    EFI_IO_FREE_BUFFER                  FreeBuffer;
} EFI_DEVICE_IO_PROTOCOL;

typedef struct _EFI_DEVICE_IO_PROTOCOL _EFI_DEVICE_IO_INTERFACE;
typedef EFI_DEVICE_IO_PROTOCOL EFI_DEVICE_IO_INTERFACE;

/* Graphics output protocol */
#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
   { 0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a } }
typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef struct {
  uint32            RedMask;
  uint32            GreenMask;
  uint32            BlueMask;
  uint32            ReservedMask;
} EFI_PIXEL_BITMASK;

typedef enum {
  PixelRedGreenBlueReserved8BitPerColor,
  PixelBlueGreenRedReserved8BitPerColor,
  PixelBitMask,
  PixelBltOnly,
  PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct {
  uint32                     Version;
  uint32                     HorizontalResolution;
  uint32                     VerticalResolution;
  EFI_GRAPHICS_PIXEL_FORMAT  PixelFormat;
  EFI_PIXEL_BITMASK          PixelInformation;
  uint32                     PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

/**
  Return the current video mode information.

  @param  This       Protocol instance pointer.
  @param  ModeNumber The mode number to return information on.
  @param  SizeOfInfo A pointer to the size,bytes, of the Info buffer.
  @param  Info       A pointer to callee allocated buffer that returns information about ModeNumber.

  @retval EFI_SUCCESS           Mode information returned.
  @retval EFI_BUFFER_TOO_SMALL  The Info buffer was too small.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to retrieve the video mode.
  @retval EFI_NOT_STARTED       Video display is not initialized. Call SetMode ()
  @retval EFI_INVALID_PARAMETER One of the input args was NULL.

**/
typedef uintn ( *EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) (
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
  uint32                                ModeNumber,
 uintn                                 *SizeOfInfo,
 EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info
  )
;

/**
  Return the current video mode information.

  @param  This              Protocol instance pointer.
  @param  ModeNumber        The mode number to be set.

  @retval EFI_SUCCESS       Graphics mode was changed.
  @retval EFI_DEVICE_ERROR  The device had an error and could not complete the request.
  @retval EFI_UNSUPPORTED   ModeNumber is not supported by this device.

**/
typedef uintn ( *EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) (
  EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
  uint32                       ModeNumber
  );

typedef struct {
  uint8 Blue;
  uint8 Green;
  uint8 Red;
  uint8 Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef union {
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Pixel;
  uint32                        Raw;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL_UNION;

typedef enum {
  EfiBltVideoFill,
  EfiBltVideoToBltBuffer,
  EfiBltBufferToVideo,
  EfiBltVideoToVideo,
  EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

/**
  The following table defines actions for BltOperations:

  <B>EfiBltVideoFill</B> - Write data from the  BltBuffer pixel (SourceX, SourceY)
  directly to every pixel of the video display rectangle
  (DestinationX, DestinationY) (DestinationX + Width, DestinationY + Height).
  Only one pixel will be used from the BltBuffer. Delta is NOT used.

  <B>EfiBltVideoToBltBuffer</B> - Read data from the video display rectangle
  (SourceX, SourceY) (SourceX + Width, SourceY + Height) and place it in
  the BltBuffer rectangle (DestinationX, DestinationY )
  (DestinationX + Width, DestinationY + Height). If DestinationX or
  DestinationY is not zero then Delta must be set to the lengthbytes
  of a rowthe BltBuffer.

  <B>EfiBltBufferToVideo</B> - Write data from the  BltBuffer rectangle
  (SourceX, SourceY) (SourceX + Width, SourceY + Height) directly to the
  video display rectangle (DestinationX, DestinationY)
  (DestinationX + Width, DestinationY + Height). If SourceX or SourceY is
  not zero then Delta must be set to the lengthbytes of a rowthe
  BltBuffer.

  <B>EfiBltVideoToVideo</B> - Copy from the video display rectangle (SourceX, SourceY)
  (SourceX + Width, SourceY + Height) .to the video display rectangle
  (DestinationX, DestinationY) (DestinationX + Width, DestinationY + Height).
  The BltBuffer and Delta  are not usedthis mode.

  @param  This         Protocol instance pointer.
  @param  BltBuffer    Buffer containing data to blit into video buffer. This
                       buffer has a size of Width*Height*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  @param  BltOperation Operation to perform on BlitBuffer and video memory
  @param  SourceX      X coordinate of source for the BltBuffer.
  @param  SourceY      Y coordinate of source for the BltBuffer.
  @param  DestinationX X coordinate of destination for the BltBuffer.
  @param  DestinationY Y coordinate of destination for the BltBuffer.
  @param  Width        Width of rectangleBltBufferpixels.
  @param  Height       Hight of rectangleBltBufferpixels.
  @param  Delta       

  @retval EFI_SUCCESS           The Blt operation completed.
  @retval EFI_INVALID_PARAMETER BltOperation is not valid.
  @retval EFI_DEVICE_ERROR      A hardware error occured writting to the video buffer.

**/
typedef uintn ( *EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) (
  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,  
  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
  uintn                                   SourceX,
  uintn                                   SourceY,
  uintn                                   DestinationX,
  uintn                                   DestinationY,
  uintn                                   Width,
  uintn                                   Height,
  uintn                                   Delta        
  );

typedef struct {
  uint32                                 MaxMode;
  uint32                                 Mode;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION   *Info;
  uintn                                  SizeOfInfo;
  EFI_PHYSICAL_ADDRESS                   FrameBufferBase;
  uintn                                  FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
  EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE  QueryMode;
  EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE    SetMode;
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT         Blt;
  EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE        *Mode;
};



/*
 * EFI EDID Discovered Protocol
 * UEFI Specification Version 2.5 Section 11.9
 */
#define EFI_EDID_DISCOVERED_PROTOCOL_GUID \
    { 0x1C0C34F6, 0xD380, 0x41FA, { 0xA0, 0x49, 0x8a, 0xD0, 0x6C, 0x1A, 0x66, 0xAA} }

typedef struct _EFI_EDID_DISCOVERED_PROTOCOL {
    uint32   SizeOfEdid;
    uint8   *Edid;
} EFI_EDID_DISCOVERED_PROTOCOL;



/*
 * EFI EDID Active Protocol
 * UEFI Specification Version 2.5 Section 11.9
 */
#define EFI_EDID_ACTIVE_PROTOCOL_GUID \
    { 0xBD8C1056, 0x9F36, 0x44EC, { 0x92, 0xA8, 0xA6, 0x33, 0x7F, 0x81, 0x79, 0x86} }

typedef struct _EFI_EDID_ACTIVE_PROTOCOL {
    uint32   SizeOfEdid;
    uint8   *Edid;
} EFI_EDID_ACTIVE_PROTOCOL;



/*
 * EFI EDID Override Protocol
 * UEFI Specification Version 2.5 Section 11.9
 */
#define EFI_EDID_OVERRIDE_PROTOCOL_GUID \
    { 0x48ECB431, 0xFB72, 0x45C0, { 0xA9, 0x22, 0xF4, 0x58, 0xFE, 0x04, 0x0B, 0xD5} }

INTERFACE_DECL(_EFI_EDID_OVERRIDE_PROTOCOL);

typedef uintn ( *EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID) (
      struct _EFI_EDID_OVERRIDE_PROTOCOL   *This,
      EFI_HANDLE                           *ChildHandle,
     uint32                               *Attributes,
 uintn                                *EdidSize,
 uint8                               **Edid);

typedef struct _EFI_EDID_OVERRIDE_PROTOCOL {
    EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID  GetEdid;
} EFI_EDID_OVERRIDE_PROTOCOL;



INTERFACE_DECL(_EFI_SERVICE_BINDING);

typedef uintn ( *EFI_SERVICE_BINDING_CREATE_CHILD) (
   struct _EFI_SERVICE_BINDING *This,
   EFI_HANDLE                  *ChildHandle
    );

typedef uintn ( *EFI_SERVICE_BINDING_DESTROY_CHILD) (
   struct _EFI_SERVICE_BINDING *This,
   EFI_HANDLE                  ChildHandle
    );

typedef struct _EFI_SERVICE_BINDING {
    EFI_SERVICE_BINDING_CREATE_CHILD  CreateChild;
    EFI_SERVICE_BINDING_DESTROY_CHILD DestroyChild;
} EFI_SERVICE_BINDING;



/*
 * EFI Driver Binding Protocol
 * UEFI Specification Version 2.5 Section 10.1
 */
#define EFI_DRIVER_BINDING_PROTOCOL_GUID \
    { 0x18A031AB, 0xB443, 0x4D1A, { 0xA5, 0xC0, 0x0C, 0x09, 0x26, 0x1E, 0x9F, 0x71} }
#define DRIVER_BINDING_PROTOCOL EFI_DRIVER_BINDING_PROTOCOL_GUID

INTERFACE_DECL(_EFI_DRIVER_BINDING_PROTOCOL);

typedef uintn ( *EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED) (
      struct _EFI_DRIVER_BINDING_PROTOCOL *This,
      EFI_HANDLE                          ControllerHandle,
      EFI_DEVICE_PATH                     *RemainingDevicePath);

typedef uintn ( *EFI_DRIVER_BINDING_PROTOCOL_START) (
      struct _EFI_DRIVER_BINDING_PROTOCOL *This,
      EFI_HANDLE                          ControllerHandle,
      EFI_DEVICE_PATH                     *RemainingDevicePath);

typedef uintn ( *EFI_DRIVER_BINDING_PROTOCOL_STOP) (
      struct _EFI_DRIVER_BINDING_PROTOCOL *This,
      EFI_HANDLE                          ControllerHandle,
      uintn                               NumberOfChildren,
      EFI_HANDLE                          *ChildHandleBuffer);

typedef struct _EFI_DRIVER_BINDING_PROTOCOL {
  EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED       Supported;
  EFI_DRIVER_BINDING_PROTOCOL_START           Start;
  EFI_DRIVER_BINDING_PROTOCOL_STOP            Stop;
  uint32                                      Version;
  EFI_HANDLE                                  ImageHandle;
  EFI_HANDLE                                  DriverBindingHandle;
} EFI_DRIVER_BINDING_PROTOCOL;

typedef struct _EFI_DRIVER_BINDING_PROTOCOL _EFI_DRIVER_BINDING;
typedef EFI_DRIVER_BINDING_PROTOCOL EFI_DRIVER_BINDING;


/*
 * Backwards compatibility with older GNU-EFI versions. Deprecated.
 */
#define EFI_DRIVER_SUPPORTED         EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED
#define EFI_DRIVER_START             EFI_DRIVER_BINDING_PROTOCOL_START
#define EFI_DRIVER_STOP              EFI_DRIVER_BINDING_PROTOCOL_STOP



/*
 * EFI Component Name Protocol
 * Deprecated - use EFI Component Name 2 Protocol instead
 */
#define EFI_COMPONENT_NAME_PROTOCOL_GUID \
    {0x107A772C, 0xD5E1, 0x11D4, { 0x9A, 0x46, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D} }
#define COMPONENT_NAME_PROTOCOL EFI_COMPONENT_NAME_PROTOCOL_GUID

INTERFACE_DECL(_EFI_COMPONENT_NAME_PROTOCOL);

typedef uintn ( *EFI_COMPONENT_NAME_GET_DRIVER_NAME) (
      struct _EFI_COMPONENT_NAME_PROTOCOL   *This,
      char                                 *Language,
     uint16                                **DriverName);

typedef uintn ( *EFI_COMPONENT_NAME_GET_CONTROLLER_NAME) (
      struct _EFI_COMPONENT_NAME_PROTOCOL   *This,
      EFI_HANDLE                            ControllerHandle,
      EFI_HANDLE                            ChildHandle,
      char                                 *Language,
     uint16                                **ControllerName);

typedef struct _EFI_COMPONENT_NAME_PROTOCOL {
  EFI_COMPONENT_NAME_GET_DRIVER_NAME      GetDriverName;
  EFI_COMPONENT_NAME_GET_CONTROLLER_NAME  GetControllerName;
  char                                   *SupportedLanguages;
} EFI_COMPONENT_NAME_PROTOCOL;

typedef struct _EFI_COMPONENT_NAME_PROTOCOL _EFI_COMPONENT_NAME;
typedef EFI_COMPONENT_NAME_PROTOCOL EFI_COMPONENT_NAME;


/*
 * EFI Component Name 2 Protocol
 * UEFI Specification Version 2.5 Section 10.5
 */
#define EFI_COMPONENT_NAME2_PROTOCOL_GUID \
    {0x6A7A5CFF, 0xE8D9, 0x4F70, { 0xBA, 0xDA, 0x75, 0xAB, 0x30, 0x25, 0xCE, 0x14} }
#define COMPONENT_NAME2_PROTOCOL EFI_COMPONENT_NAME2_PROTOCOL_GUID

INTERFACE_DECL(_EFI_COMPONENT_NAME2_PROTOCOL);

typedef uintn ( *EFI_COMPONENT_NAME2_GET_DRIVER_NAME) (
      struct _EFI_COMPONENT_NAME2_PROTOCOL   *This,
      char                                  *Language,
     uint16                                 **DriverName);

typedef uintn ( *EFI_COMPONENT_NAME2_GET_CONTROLLER_NAME) (
      struct _EFI_COMPONENT_NAME2_PROTOCOL   *This,
      EFI_HANDLE                             ControllerHandle,
      EFI_HANDLE                             ChildHandle,
      char                                  *Language,
     uint16                                 **ControllerName);

typedef struct _EFI_COMPONENT_NAME2_PROTOCOL {
  EFI_COMPONENT_NAME2_GET_DRIVER_NAME       GetDriverName;
  EFI_COMPONENT_NAME2_GET_CONTROLLER_NAME   GetControllerName;
  char                                     *SupportedLanguages;
} EFI_COMPONENT_NAME2_PROTOCOL;

typedef struct _EFI_COMPONENT_NAME2_PROTOCOL _EFI_COMPONENT_NAME2;
typedef EFI_COMPONENT_NAME2_PROTOCOL EFI_COMPONENT_NAME2;



/*
 * EFI Loaded Image Protocol
 * UEFI Specification Version 2.5 Section 8.1
 */
#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
    { 0x5B1B31A1, 0x9562, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B} }
#define LOADED_IMAGE_PROTOCOL EFI_LOADED_IMAGE_PROTOCOL_GUID

#define EFI_LOADED_IMAGE_PROTOCOL_REVISION  0x1000
#define EFI_IMAGE_INFORMATION_REVISION  EFI_LOADED_IMAGE_PROTOCOL_REVISION

typedef uintn ( *EFI_IMAGE_UNLOAD) (
   EFI_HANDLE                   ImageHandle
    );

typedef struct {
    uint32                          Revision;
    EFI_HANDLE                      ParentHandle;
    struct _EFI_SYSTEM_TABLE        *SystemTable;

    // Source location of image
    EFI_HANDLE                      DeviceHandle;
    EFI_DEVICE_PATH                 *FilePath;
   void                           *Reserved;

    // Images load options
    uint32                          LoadOptionsSize;
   void                           *LoadOptions;

    // Location of where image was loaded
   void                           *ImageBase;
    uint64                          ImageSize;
    EFI_MEMORY_TYPE                 ImageCodeType;
    EFI_MEMORY_TYPE                 ImageDataType;

    // If the driver image supports a dynamic unload request
    EFI_IMAGE_UNLOAD                Unload;
} EFI_LOADED_IMAGE_PROTOCOL;

typedef EFI_LOADED_IMAGE_PROTOCOL EFI_LOADED_IMAGE;

#define EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID \
    {0xbc62157e, 0x3e33, 0x4fec, {0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf} }

/*
 * Random Number Generator Protocol
 * UEFI Specification Version 2.5 Section 35.5
 */
#define EFI_RNG_PROTOCOL_GUID                          \
          { 0x3152bca5, 0xeade, 0x433d, {0x86, 0x2e, 0xc0, 0x1c, 0xdc, 0x29, 0x1f, 0x44} }

typedef EFI_GUID EFI_RNG_ALGORITHM;

#define EFI_RNG_ALGORITHM_SP800_90_HASH_256_GUID       \
     {0xa7af67cb, 0x603b, 0x4d42, {0xba, 0x21, 0x70, 0xbf, 0xb6, 0x29, 0x3f, 0x96} }

#define EFI_RNG_ALGORITHM_SP800_90_HMAC_256_GUID       \
     {0xc5149b43, 0xae85, 0x4f53, {0x99, 0x82, 0xb9, 0x43, 0x35, 0xd3, 0xa9, 0xe7} }

#define EFI_RNG_ALGORITHM_SP800_90_CTR_256_GUID        \
     {0x44f0de6e, 0x4d8c, 0x4045, {0xa8, 0xc7, 0x4d, 0xd1, 0x68, 0x85, 0x6b, 0x9e} }

#define EFI_RNG_ALGORITHM_X9_31_3DES_GUID              \
     {0x63c4785a, 0xca34, 0x4012, {0xa3, 0xc8, 0x0b, 0x6a, 0x32, 0x4f, 0x55, 0x46} }

#define EFI_RNG_ALGORITHM_X9_31_AES_GUID               \
     {0xacd03321, 0x777e, 0x4d3d, {0xb1, 0xc8, 0x20, 0xcf, 0xd8, 0x88, 0x20, 0xc9} }

#define EFI_RNG_ALGORITHM_RAW                          \
     {0xe43176d7, 0xb6e8, 0x4827, {0xb7, 0x84, 0x7f, 0xfd, 0xc4, 0xb6, 0x85, 0x61} }

INTERFACE_DECL(_EFI_RNG_PROTOCOL);

typedef uintn ( *EFI_RNG_GET_INFO) (
      struct _EFI_RNG_PROTOCOL   *This,
 uintn                      *RNGAlgorithmListSize,
     EFI_RNG_ALGORITHM          *RNGAlgorithmList
);

typedef uintn ( *EFI_RNG_GET_RNG) (
      struct _EFI_RNG_PROTOCOL   *This,
      EFI_RNG_ALGORITHM          *RNGAlgorithm,          
      uintn                      RNGValueLength,
     uint8                      *RNGValue
);

typedef struct _EFI_RNG_PROTOCOL {
          EFI_RNG_GET_INFO           GetInfo;
          EFI_RNG_GET_RNG            GetRNG;
} EFI_RNG_PROTOCOL;


//
// EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL
//

#define EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID          \
          { 0x6b30c738, 0xa391, 0x11d4, {0x9a, 0x3b, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

INTERFACE_DECL(_EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL);

typedef uintn ( *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER) (
     struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
     EFI_HANDLE                                      ControllerHandle,
    EFI_HANDLE                                     *DriverImageHandle);

typedef uintn ( *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH) (
     struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
     EFI_HANDLE                                      ControllerHandle,
EFI_DEVICE_PATH                               **DriverImagePath);

typedef uintn ( *EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED) (
     struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
     EFI_HANDLE                                      ControllerHandle,
     EFI_DEVICE_PATH                                *DriverImagePath,
     EFI_HANDLE                                      DriverImageHandle);

typedef struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL {
  EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER       GetDriver;
  EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH  GetDriverPath;
  EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED    DriverLoaded;
} EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL;

//
// EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL
//

#define EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID          \
          { 0x3bc1b285, 0x8a15, 0x4a82, {0xaa, 0xbf, 0x4d, 0x7d, 0x13, 0xfb, 0x32, 0x65} }

INTERFACE_DECL(_EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL);

typedef uintn ( *EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER) (
     struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL  *This,
EFI_HANDLE                                         *DriverImageHandle);

typedef struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL {
  EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER       GetDriver;
} EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL;

//
// EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL
//

#define EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL_GUID          \
          { 0xb1ee129e, 0xda36, 0x4181, {0x91, 0xf8, 0x04, 0xa4, 0x92, 0x37, 0x66, 0xa7} }

INTERFACE_DECL(_EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL);

typedef
uint32
( *EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION) (
     struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL  *This);

typedef struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL {
  EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION       GetVersion;
} EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL;

//
// EFI_EBC_PROTOCOL
//

#define EFI_EBC_INTERPRETER_PROTOCOL_GUID              \
     {0x13ac6dd1, 0x73d0, 0x11d4, {0xb0, 0x6b, 0x00, 0xaa, 0x00, 0xbd, 0x6d, 0xe7} }

#define EFI_EBC_PROTOCOL_GUID EFI_EBC_INTERPRETER_PROTOCOL_GUID

INTERFACE_DECL(_EFI_EBC_PROTOCOL);

typedef uintn ( *EFI_EBC_CREATE_THUNK)(
 struct _EFI_EBC_PROTOCOL   *This,
 EFI_HANDLE                 ImageHandle,
void                      *EbcEntryPoint,
void                     **Thunk);

typedef uintn ( *EFI_EBC_UNLOAD_IMAGE)(
 struct _EFI_EBC_PROTOCOL   *This,
 EFI_HANDLE                 ImageHandle);

typedef uintn ( *EBC_ICACHE_FLUSH)(
 EFI_PHYSICAL_ADDRESS       Start,
 uint64                     Length);

typedef uintn ( *EFI_EBC_REGISTER_ICACHE_FLUSH)(
 struct _EFI_EBC_PROTOCOL   *This,
 EBC_ICACHE_FLUSH           Flush);

typedef uintn ( *EFI_EBC_GET_VERSION)(
 struct _EFI_EBC_PROTOCOL   *This,
uint64                 *Version);

typedef struct _EFI_EBC_PROTOCOL {
  EFI_EBC_CREATE_THUNK          CreateThunk;
  EFI_EBC_UNLOAD_IMAGE          UnloadImage;
  EFI_EBC_REGISTER_ICACHE_FLUSH RegisterICacheFlush;
  EFI_EBC_GET_VERSION           GetVersion;
} EFI_EBC_PROTOCOL;

