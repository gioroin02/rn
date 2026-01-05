#ifndef PX_SYSTEM_STORAGE_FILE_C
#define PX_SYSTEM_STORAGE_FILE_C

#include "file.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../win32/storage/export.c"

    #define __pxFileReserve__       pxWin32FileReserve
    #define __pxFileDefaultInput__  pxWin32FileDefaultInput
    #define __pxFileDefaultOutput__ pxWin32FileDefaultOutput
    #define __pxFileDefaultError__  pxWin32FileDefaultError
    #define __pxFileDestroy__       pxWin32FileDestroy
    #define __pxFileWrite__         pxWin32FileWrite
    #define __pxFileRead__          pxWin32FileRead

#else

    #error "Unknown platform"

#endif

PxFile*
pxFileReserve(PxMemoryArena* arena)
{
    return __pxFileReserve__(arena);
}

b32
pxFileDefaultInput(PxFile* self)
{
    return __pxFileDefaultInput__(self);
}

b32
pxFileDefaultOutput(PxFile* self)
{
    return __pxFileDefaultOutput__(self);
}

b32
pxFileDefaultError(PxFile* self)
{
    return __pxFileDefaultError__(self);
}

void
pxFileDestroy(PxFile* self)
{
    return __pxFileDestroy__(self);
}

ssize
pxFileWrite(PxFile* self, u8* values, ssize start, ssize stop)
{
    return __pxFileWrite__(self, values, start, stop);
}

ssize
pxFileRead(PxFile* self, u8* values, ssize start, ssize stop)
{
    return __pxFileRead__(self, values, start, stop);
}

#endif // PX_SYSTEM_STORAGE_FILE_C
