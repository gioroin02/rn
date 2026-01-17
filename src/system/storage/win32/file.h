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

PWin32File* pWin32FileReserve(PMemoryArena* arena);

void pWin32FileDestroy(PWin32File* self);

Int pWin32FileWrite(PWin32File* self, U8* pntr, Int start, Int stop);

Int pWin32FileRead(PWin32File* self, U8* pntr, Int start, Int stop);

#endif // P_SYSTEM_WIN32_STORAGE_FILE_H
