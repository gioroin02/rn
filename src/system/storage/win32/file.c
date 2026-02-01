#ifndef RHO_SYSTEM_WIN32_STORAGE_FILE_C
#define RHO_SYSTEM_WIN32_STORAGE_FILE_C

#include "file.h"

static RString16 rho_win32_utf16_from_utf8(RString8 string, RChar16* buffer, RInt size)
{
    RChar8* pntr   = (RChar8*) string.values;
    RInt    length = string.size;

    size = MultiByteToWideChar(CP_UTF8, 0,
        pntr, length, (RUint16*) buffer, size);

    for (RInt i = 0; i < size; i += 1) {
        if (buffer[i] == 0x5C) buffer[i] = 0x2F;
    }

    return rho_string16_make(buffer, size);
}

RBool32 rho_win32_file_find(RString8 name, RFileAttribs* attribs)
{
    WIN32_FILE_ATTRIBUTE_DATA data = {0};

    RChar16 buffer[4 * RHO_MEMORY_KIB] = {0};

    rho_memory_set(attribs, sizeof *attribs, 0xAB);

    attribs->kind = RFileKind_None;
    attribs->perm = RFilePerm_None;
    attribs->size = 0;

    RString16 name16 =
        rho_win32_utf16_from_utf8(name, buffer, sizeof buffer);

    BOOL status = GetFileAttributesExW((RUint16*) name16.values,
        GetFileExInfoStandard, &data);

    if (name16.size <= 0 || status == 0) return 0;

    if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
        ULARGE_INTEGER value;

        value.HighPart = data.nFileSizeHigh;
        value.LowPart  = data.nFileSizeLow;

        attribs->kind  = RFileKind_Regular;
        attribs->size  = value.QuadPart;
        attribs->perm |= RFilePerm_Read;
    }
    else attribs->kind = RFileKind_Directory;

    return 1;
}

RBool32 rho_win32_file_delete(RString8 name)
{
    return 0;
}

RWin32File* rho_win32_file_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RWin32File, 1);
}

RBool32 rho_win32_file_open(RWin32File* self, RString8 name, RFileMode mode)
{
    RChar16 buffer[4 * RHO_MEMORY_KIB] = {0};

    rho_memory_set(self, sizeof *self, 0xAB);

    self->handle  = NULL;
    self->overlap = (OVERLAPPED) {0};

    RInt action = OPEN_EXISTING;
    RInt access = 0;
    RInt flag   = FILE_FLAG_OVERLAPPED;

    if ((mode & RFileMode_New)    != 0) action = CREATE_NEW;
    if ((mode & RFileMode_Always) != 0) action = OPEN_ALWAYS;
    if ((mode & RFileMode_Empty)  != 0) action = TRUNCATE_EXISTING;

    if ((mode & RFileMode_Always) != 0 && (mode & RFileMode_Empty) != 0)
        action = CREATE_ALWAYS;

    if ((mode & RFileMode_Read)  != 0) access |= GENERIC_READ;
    if ((mode & RFileMode_Write) != 0) access |= GENERIC_WRITE;

    RString16 name16 =
        rho_win32_utf16_from_utf8(name, buffer, sizeof buffer);

    if (name16.size <= 0 || action == 0 || access == 0) return 0;

    HANDLE handle = CreateFileW((RUint16*) name16.values, access,
        FILE_SHARE_READ, 0, action, FILE_ATTRIBUTE_NORMAL | flag, 0);

    if (handle == INVALID_HANDLE_VALUE) return 0;

    self->handle = handle;

    return 1;
}

void rho_win32_file_close(RWin32File* self)
{
    if (self->handle != INVALID_HANDLE_VALUE)
        CloseHandle(self->handle);

    rho_memory_set(self, sizeof *self, 0xAB);
}

RInt rho_win32_file_write(RWin32File* self, RUint8* pntr, RInt start, RInt stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    result = 0;
    RInt    count  = 0;

    self->overlap        = (OVERLAPPED) {0};
    self->overlap.hEvent = CreateEvent(NULL, 1, 0, NULL);

    if (self->overlap.hEvent == NULL) return 0;

    while (result < size) {
        RBool32 status = WriteFile(self->handle, memory + result,
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

RInt rho_win32_file_read(RWin32File* self, RUint8* pntr, RInt start, RInt stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    count  = 0;

    self->overlap        = (OVERLAPPED) {0};
    self->overlap.hEvent = CreateEvent(NULL, 1, 0, NULL);

    if (self->overlap.hEvent == NULL) return 0;

    RBool32 status = ReadFile(self->handle, memory, size,
        (DWORD*) &count, &self->overlap);

    if (status == 0 && GetLastError() == ERROR_IO_PENDING) {
        status = GetOverlappedResult(self->handle,
            &self->overlap, (DWORD*) &count, 1);
    }

    CloseHandle(self->overlap.hEvent);

    if (status != 0 && count > 0 && count <= size) return count;

    return 0;
}

#endif
