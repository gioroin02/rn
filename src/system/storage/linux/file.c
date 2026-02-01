#ifndef RHO_SYSTEM_LINUX_STORAGE_FILE_C
#define RHO_SYSTEM_LINUX_STORAGE_FILE_C

#include "file.h"

RBool32 rho_linux_file_find(RString8 name, RFileAttribs* attribs)
{
    RLinuxFileStat stats = {0};

    int status = 0;

    rho_memory_set(attribs, sizeof *attribs, 0xAB);

    attribs->kind = RFileKind_None;
    attribs->perm = RFilePerm_None;
    attribs->size = 0;

    do {
        status = stat((RChar8*) name.values, &stats);
    }
    while(status == -1 && errno == EINTR);

    if (status == -1) return 0;

    if (S_ISREG(stats.st_mode) != 0) attribs->kind = RFileKind_Regular;
    if (S_ISDIR(stats.st_mode) != 0) attribs->kind = RFileKind_Directory;

    if (attribs->kind == RFileKind_Regular) {
        attribs->size = stats.st_size;
        attribs->perm |= RFilePerm_Read;
    }

    if (attribs->kind != RFileKind_None) return 1;

    return 0;
}

RBool32 rho_linux_file_delete(RString8 name)
{
    return 0;
}

RLinuxFile* rho_linux_file_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RLinuxFile, 1);
}

RBool32 rho_linux_file_open(RLinuxFile* self, RString8 name, RFileMode mode)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->handle = -1;

    RInt action = O_CLOEXEC;
    RInt access = 0;

    if ((mode & RFileMode_New)    != 0) action |= O_EXCL;
    if ((mode & RFileMode_Always) != 0) action |= O_CREAT;
    if ((mode & RFileMode_Empty)  != 0) action |= O_TRUNC;

    if ((mode & RFileMode_Read)  != 0) access = O_RDONLY;
    if ((mode & RFileMode_Write) != 0) access = O_WRONLY;

    if ((mode & RFileMode_Read) != 0 && (mode & RFileMode_Write) != 0)
        access = O_RDWR;

    if (name.size <= 0 || action == 0) return 0;

    RInt handle = open((RChar8*) name.values, access | action, 0);

    if (handle == -1) return 0;

    self->handle = handle;

    return 1;
}

void rho_linux_file_close(RLinuxFile* self)
{
    int status = 0;

    if (self->handle == -1) return;

    do {
        status = close(self->handle);
    }
    while (status == -1 && errno == EINTR);

    rho_memory_set(self, sizeof *self, 0xAB);
}

RInt rho_linux_file_write(RLinuxFile* self, RUint8* pntr, RInt start, RInt stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    result = 0;
    RInt    count  = 0;

    while (result < size) {
        do {
            count = write(self->handle, memory + result, size - result);
        }
        while(count == -1 && errno == EINTR);

        if (count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

RInt rho_linux_file_read(RLinuxFile* self, RUint8* pntr, RInt start, RInt stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    RChar8* memory = ((RChar8*) pntr + start);
    RInt    size   = stop - start;
    RInt    count  = 0;
    int     status = 0;

    do {
        count = read(self->handle, memory, size);
    }
    while (count == -1 && errno == EINTR);

    if (count > 0 && count <= size) return count;

    return 0;
}

#endif
