#ifndef PX_WIN32_STORAGE_FILE_C
#define PX_WIN32_STORAGE_FILE_C

#include "file.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct PxWin32File
{
    // TODO(gio): add perms.
    HANDLE handle;
};

PxWin32File*
pxWin32FileReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32File);
}

b32
pxWin32FileDefaultInput(PxWin32File* self)
{
    pxMemorySet(self, sizeof *self, 0xAB);

    HANDLE stdin = GetStdHandle(STD_INPUT_HANDLE);

    if (stdin == INVALID_HANDLE_VALUE) return 0;

    self->handle = stdin;

    return 1;
}

b32
pxWin32FileDefaultOutput(PxWin32File* self)
{
    pxMemorySet(self, sizeof *self, 0xAB);

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (stdout == INVALID_HANDLE_VALUE) return 0;

    self->handle = stdout;

    return 1;
}

b32
pxWin32FileDefaultError(PxWin32File* self)
{
    pxMemorySet(self, sizeof *self, 0xAB);

    HANDLE stderr = GetStdHandle(STD_ERROR_HANDLE);

    if (stderr == INVALID_HANDLE_VALUE) return 0;

    self->handle = stderr;

    return 1;
}

void
pxWin32FileDestroy(PxWin32File* self)
{
    if (self->handle != INVALID_HANDLE_VALUE)
        CloseHandle(self->handle);

    pxMemorySet(self, sizeof *self, 0xAB);
}

ssize
pxWin32FileWrite(PxWin32File* self, u8* values, ssize start, ssize stop)
{
    if (values == PX_NULL || stop <= start || start < 0) return 0;

    char* pntr   = ((char*) values + start);
    ssize size   = stop - start;
    ssize result = 0;

    while (result < size) {
        DWORD count = 0;

        b32 status = WriteFile(self->handle, pntr + result,
            ((DWORD) size - result), &count, 0);

        if (status != 0 && count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

ssize
pxWin32FileRead(PxWin32File* self, u8* values, ssize start, ssize stop)
{
    if (values == PX_NULL || stop <= start || start < 0) return 0;

    char* pntr  = ((char*) values + start);
    ssize size  = stop - start;
    DWORD count = 0;

    b32 status = ReadFile(self->handle, pntr, (DWORD) size, &count, 0);

    if (status != 0 && count > 0 && count <= size)
        return count;

    return 0;
}

#endif // PX_WIN32_STORAGE_FILE_C
