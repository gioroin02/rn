#ifndef RHO_SYSTEM_WIN32_STORAGE_FILE_H
#define RHO_SYSTEM_WIN32_STORAGE_FILE_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN
#define NOGDI

#include <windows.h>

typedef struct RWin32File
{
    HANDLE     handle;
    OVERLAPPED overlap;
}
RWin32File;

RBool32 rho_win32_file_find(RString8 name, RFileAttribs* attribs);

RBool32 rho_win32_file_delete(RString8 name);

RWin32File* rho_win32_file_reserve(RMemoryArena* arena);

RBool32 rho_win32_file_open(RWin32File* self, RString8 name, RFileMode mode);

void rho_win32_file_close(RWin32File* self);

RInt rho_win32_file_write(RWin32File* self, RUint8* pntr, RInt start, RInt stop);

RInt rho_win32_file_read(RWin32File* self, RUint8* pntr, RInt start, RInt stop);

#endif
