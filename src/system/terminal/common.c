#ifndef PX_SYSTEM_TERMINAL_COMMON_C
#define PX_SYSTEM_TERMINAL_COMMON_C

#include "common.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../win32/terminal/export.c"

    #define __pxTerminalReserve__ pxWin32TerminalReserve
    #define __pxTerminalCreate__  pxWin32TerminalCreate
    #define __pxTerminalDestroy__ pxWin32TerminalDestroy
    #define __pxTerminalModeSet__ pxWin32TerminalModeSet
    #define __pxTerminalModeGet__ pxWin32TerminalModeGet

#else

    #error "Unknown platform"

#endif

PxTerminal*
pxTerminalReserve(PxMemoryArena* arena)
{
    return __pxTerminalReserve__(arena);
}

b32
pxTerminalCreate(PxTerminal* self)
{
    return __pxTerminalCreate__(self);
}

void
pxTerminalDestroy(PxTerminal* self)
{
    return __pxTerminalDestroy__(self);
}

b32
pxTerminalModeSet(PxTerminal* self, PxTerminalMode mode)
{
    return __pxTerminalModeSet__(self, mode);
}

PxTerminalMode
pxTerminalModeGet(PxTerminal* self)
{
    return __pxTerminalModeGet__(self);
}

#endif // PX_SYSTEM_TERMINAL_COMMON_C
