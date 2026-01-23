#ifndef P_SYSTEM_STORAGE_FILE_C
#define P_SYSTEM_STORAGE_FILE_C

#include "file.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PFile__ PWin32File

    #define __pFileReserve__ pWin32FileReserve
    #define __pFileDestroy__ pWin32FileDestroy
    #define __pFileWrite__   pWin32FileWrite
    #define __pFileRead__    pWin32FileRead

#else

    #error "Unknown platform"

#endif

PFile*
pFileReserve(PMemoryArena* arena)
{
    return (PFile*) __pFileReserve__(arena);
}

void pFileDestroy(PFile* self)
{
    return __pFileDestroy__((__PFile__*) self);
}

Int pFileWrite(PFile* self, U8* pntr, Int start, Int stop)
{
    return __pFileWrite__((__PFile__*) self, pntr, start, stop);
}

Int pFileRead(PFile* self, U8* pntr, Int start, Int stop)
{
    return __pFileRead__((__PFile__*) self, pntr, start, stop);
}

#endif
