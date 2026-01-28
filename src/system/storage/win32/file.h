#ifndef P_SYSTEM_WIN32_STORAGE_FILE_H
#define P_SYSTEM_WIN32_STORAGE_FILE_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN
#define NOGDI

#include <windows.h>

typedef struct PWin32File
{
    HANDLE     handle;
    OVERLAPPED overlap;
}
PWin32File;

B32 pWin32FileAttribs(PString8 name, PFileAttribs* attribs);

B32 pWin32FileDestroy(PString8 name);

PWin32File* pWin32FileReserve(PMemoryArena* arena);

B32 pWin32FileOpen(PWin32File* self, PString8 name, PFileMode mode);

void pWin32FileClose(PWin32File* self);

Int pWin32FileWrite(PWin32File* self, U8* pntr, Int start, Int stop);

Int pWin32FileRead(PWin32File* self, U8* pntr, Int start, Int stop);

#endif
