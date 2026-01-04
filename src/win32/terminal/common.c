#ifndef PX_WIN32_TERMINAL_COMMON_C
#define PX_WIN32_TERMINAL_COMMON_C

#include "common.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct PxWin32Terminal
{
    PxTerminalMode mode;

    DWORD conf_stdin;
    DWORD conf_stdout;
};

static b32
pxWin32TerminalModeSetCooked(PxWin32Terminal* self)
{
    HANDLE stdin  = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (stdin == INVALID_HANDLE_VALUE || stdout == INVALID_HANDLE_VALUE)
        return 0;

    if (self->mode != PxTerminalMode_Cooked) {
        SetConsoleMode(stdin, self->conf_stdin);
        SetConsoleMode(stdout, self->conf_stdout);

        self->mode = PxTerminalMode_Cooked;
    }

    return 1;
}

static b32
pxWin32TerminalModeSetRaw(PxWin32Terminal* self)
{
    HANDLE stdin  = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (stdin == INVALID_HANDLE_VALUE || stdout == INVALID_HANDLE_VALUE)
        return 0;

    if (self->mode != PxTerminalMode_Raw) {
        DWORD conf_stdin = ENABLE_PROCESSED_INPUT |
            ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT;

        DWORD conf_stdout = ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        SetConsoleMode(stdin, self->conf_stdin & ~conf_stdin);
        SetConsoleMode(stdout, self->conf_stdout & ~conf_stdout);

        self->mode = PxTerminalMode_Raw;
    }

    return 1;
}

PxWin32Terminal*
pxWin32TerminalReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32Terminal);
}

b32
pxWin32TerminalCreate(PxWin32Terminal* self)
{
    HANDLE stdin  = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (stdin == INVALID_HANDLE_VALUE || stdout == INVALID_HANDLE_VALUE)
        return 0;

    GetConsoleMode(stdin, &self->conf_stdin);
    GetConsoleMode(stdout, &self->conf_stdout);

    self->mode = PxTerminalMode_Cooked;

    return 1;
}

void
pxWin32TerminalDestroy(PxWin32Terminal* self)
{
    if (self->mode != PxTerminalMode_Cooked)
        pxWin32TerminalModeSetCooked(self);

    pxMemorySet(self, sizeof *self, 0xAB);
}

b32
pxWin32TerminalModeSet(PxWin32Terminal* self, PxTerminalMode mode)
{
    switch (mode) {
        case PxTerminalMode_Cooked: return pxWin32TerminalModeSetCooked(self);
        case PxTerminalMode_Raw:    return pxWin32TerminalModeSetRaw(self);

        default: break;
    }

    return 0;
}

PxTerminalMode
pxWin32TerminalModeGet(PxWin32Terminal* self)
{
    return self->mode;
}

#endif // PX_TERMINAL_COMMON_C
