#ifndef P_SYSTEM_STORAGE_FILE_C
#define P_SYSTEM_STORAGE_FILE_C

#include "file.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PFile__ PWin32File

    #define __pFileAttribs__ pWin32FileAttribs
    #define __pFileDestroy__ pWin32FileDestroy
    #define __pFileReserve__ pWin32FileReserve
    #define __pFileOpen__    pWin32FileOpen
    #define __pFileClose__   pWin32FileClose
    #define __pFileWrite__   pWin32FileWrite
    #define __pFileRead__    pWin32FileRead

#elif P_SYSTEM == P_SYSTEM_LINUX

    #include "linux/export.c"

    #define __PFile__ PLinuxFile

    #define __pFileAttribs__ pLinuxFileAttribs
    #define __pFileDestroy__ pLinuxFileDestroy
    #define __pFileReserve__ pLinuxFileReserve
    #define __pFileOpen__    pLinuxFileOpen
    #define __pFileClose__   pLinuxFileClose
    #define __pFileWrite__   pLinuxFileWrite
    #define __pFileRead__    pLinuxFileRead

#else

    #error "Unknown platform"

#endif

B32 pFileAttribs(PString8 name, PFileAttribs* attribs)
{
    return __pFileAttribs__(name, attribs);
}

B32 pFileDestroy(PString8 name)
{
    return __pFileDestroy__(name);
}

PFile* pFileReserve(PMemoryArena* arena)
{
    return (PFile*) __pFileReserve__(arena);
}

B32 pFileOpen(PFile* self, PString8 name, PFileMode mode)
{
    return __pFileOpen__((__PFile__*) self, name, mode);
}

void pFileClose(PFile* self)
{
    return __pFileClose__((__PFile__*) self);
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
