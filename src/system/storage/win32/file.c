#ifndef P_SYSTEM_WIN32_STORAGE_FILE_C
#define P_SYSTEM_WIN32_STORAGE_FILE_C

#include "file.h"

PWin32File* pWin32FileReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32File);
}

void pWin32FileDestroy(PWin32File* self)
{
    if (self->handle != INVALID_HANDLE_VALUE)
        CloseHandle(self->handle);

    pMemorySet(self, sizeof *self, 0xAB);
}

Int pWin32FileWrite(PWin32File* self, U8* pntr, Int start, Int stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int result = 0;

    pMemorySet(&self->overlap, sizeof self->overlap, 0x00);

    self->overlap.hEvent = CreateEvent(NULL, 1, 0, NULL);

    if (self->overlap.hEvent == NULL) return 0;

    while (result < size) {
        Int count = 0;

        B32 status = WriteFile(self->handle, memory + result,
            size - result, (DWORD*) &count, &self->overlap);

        if (status == 0 && GetLastError() == ERROR_IO_PENDING) {
            status = GetOverlappedResult(self->handle,
                &self->overlap, (DWORD*) &count, 1);
        }

        if (status != 0 && count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    CloseHandle(self->overlap.hEvent);

    return result;
}

Int pWin32FileRead(PWin32File* self, U8* pntr, Int start, Int stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int count  = 0;

    pMemorySet(&self->overlap, sizeof self->overlap, 0x00);

    self->overlap.hEvent = CreateEvent(NULL, 1, 0, NULL);

    if (self->overlap.hEvent == NULL) return 0;

    B32 status = ReadFile(self->handle, memory, size, (DWORD*) &count, &self->overlap);

    if (status == 0 && GetLastError() == ERROR_IO_PENDING) {
        status = GetOverlappedResult(self->handle,
            &self->overlap, (DWORD*) &count, 1);
    }

    CloseHandle(self->overlap.hEvent);

    if (status != 0 && count > 0 && count <= size) return count;

    return 0;
}

#endif
