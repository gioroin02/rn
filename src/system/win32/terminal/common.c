#ifndef PX_WIN32_TERMINAL_COMMON_C
#define PX_WIN32_TERMINAL_COMMON_C

#include "common.h"

static HANDLE
pxWin32DefaultInputHandle()
{
    DWORD perm = GENERIC_READ | GENERIC_WRITE;
    DWORD flag = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED;

    return CreateFileW(L"CONIN$", perm, FILE_SHARE_READ,
        PX_NULL, OPEN_EXISTING, flag, PX_NULL);
}

static HANDLE
pxWin32DefaultOutputHandle()
{
    DWORD perm = GENERIC_READ | GENERIC_WRITE;
    DWORD flag = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED;

    return CreateFileW(L"CONOUT$", perm, FILE_SHARE_READ,
        PX_NULL, OPEN_EXISTING, flag, PX_NULL);
}

static b32
pxWin32TerminalModeSetCooked(PxWin32Terminal* self)
{
    if (self->mode != PxTerminalMode_Cooked) {
        SetConsoleMode(self->handle_in, self->conf_in);
        SetConsoleMode(self->handle_out, self->conf_out);

        self->mode = PxTerminalMode_Cooked;
    }

    return 1;
}

static b32
pxWin32TerminalModeSetRaw(PxWin32Terminal* self)
{
    DWORD conf_in = (self->conf_in & ~(ENABLE_PROCESSED_INPUT |
        ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT)) | ENABLE_VIRTUAL_TERMINAL_INPUT;

    DWORD conf_out = self->conf_out | (ENABLE_PROCESSED_OUTPUT |
        ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);

    if (self->mode != PxTerminalMode_Raw) {
        SetConsoleMode(self->handle_in, conf_in);
        SetConsoleMode(self->handle_out, conf_out);

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
    HANDLE handle_in  = pxWin32DefaultInputHandle();
    HANDLE handle_out = pxWin32DefaultOutputHandle();

    if (handle_in != INVALID_HANDLE_VALUE && handle_out != INVALID_HANDLE_VALUE) {
        GetConsoleMode(handle_in, &self->conf_in);
        GetConsoleMode(handle_out, &self->conf_out);

        self->mode       = PxTerminalMode_Cooked;
        self->handle_in  = handle_in;
        self->handle_out = handle_out;

        return 1;
    }

    CloseHandle(handle_out);
    CloseHandle(handle_in);

    return 0;
}

void
pxWin32TerminalDestroy(PxWin32Terminal* self)
{
    if (self->mode != PxTerminalMode_Cooked)
        pxWin32TerminalModeSetCooked(self);

    CloseHandle(self->handle_out);
    CloseHandle(self->handle_in);

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
