#ifndef P_SYSTEM_WIN32_STORAGE_FILE_C
#define P_SYSTEM_WIN32_STORAGE_FILE_C

#include "file.h"

static PString16 pWin32String8To16(PString8 string, U16* buffer, Int size)
{
    PString16 result = pString16Make(buffer, size);

    result.size = MultiByteToWideChar(CP_UTF8, 0,
        (I8*) string.values, string.size, buffer, size);

    for (Int i = 0; i < result.size; i += 1) {
        if (result.values[i] == 0x5C) result.values[i] = 0x2F;
    }

    return result;
}

B32 pWin32FileAttribs(PString8 name, PFileAttribs* attribs)
{
    U16 buffer[4 * P_MEMORY_KIB] = {0};

    PString16 name16 = pWin32String8To16(name, buffer, sizeof buffer);

    if (name16.size <= 0) return 0;

    WIN32_FILE_ATTRIBUTE_DATA data = {0};

    BOOL status = GetFileAttributesExW(name16.values,
        GetFileExInfoStandard, &data);

    if (status == 0) return 0;

    if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
        ULARGE_INTEGER value;

        value.HighPart = data.nFileSizeHigh;
        value.LowPart  = data.nFileSizeLow;

        attribs->kind = PFileKind_Regular;
        attribs->size = value.QuadPart;
    }
    else attribs->kind = PFileKind_Directory;

    return 1;
}

B32 pWin32FileDestroy(PString8 name)
{
    return 0;
}

PWin32File* pWin32FileReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32File);
}

B32 pWin32FileOpen(PWin32File* self, PString8 name, PFileMode mode)
{
    U16 buffer[4 * P_MEMORY_KIB] = {0};

    pMemorySet(self, sizeof *self, 0xAB);

    Int action = OPEN_EXISTING;
    Int access = 0;

    if ((mode & PFileMode_Create) != 0) {
        action = OPEN_ALWAYS;

        if ((mode & PFileMode_Unique) != 0)
            action = CREATE_NEW;
    }

    if ((mode & PFileMode_Read)  != 0) access |= GENERIC_READ;
    if ((mode & PFileMode_Write) != 0) access |= GENERIC_WRITE;

    PString16 name16 = pWin32String8To16(name, buffer, sizeof buffer);

    if (name16.size <= 0) return 0;

    HANDLE handle = CreateFileW(buffer, access,
        FILE_SHARE_READ, 0, action, FILE_ATTRIBUTE_NORMAL, 0);

    if (handle == INVALID_HANDLE_VALUE) return 0;

    self->handle = handle;

    return 1;
}

void pWin32FileClose(PWin32File* self)
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
