#ifndef PX_WIN32_TERMINAL_COMMON_H
#define PX_WIN32_TERMINAL_COMMON_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

typedef struct PxWin32Terminal
{
    PxTerminalMode mode;

    HANDLE handle_in;
    HANDLE handle_out;

    DWORD conf_in;
    DWORD conf_out;
}
PxWin32Terminal;

PxWin32Terminal*
pxWin32TerminalReserve(PxMemoryArena* arena);

b32
pxWin32TerminalCreate(PxWin32Terminal* self);

void
pxWin32TerminalDestroy(PxWin32Terminal* self);

b32
pxWin32TerminalModeSet(PxWin32Terminal* self, PxTerminalMode mode);

PxTerminalMode
pxWin32TerminalModeGet(PxWin32Terminal* self);

#endif // PX_WIN32_TERMINAL_COMMON_H
