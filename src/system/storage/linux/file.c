#ifndef P_SYSTEM_LINUX_STORAGE_FILE_C
#define P_SYSTEM_LINUX_STORAGE_FILE_C

#include "file.h"

B32 pLinuxFileAttribs(PString8 name, PFileAttribs* attribs)
{
    PLinuxFileStat stats = {0};

    int status = 0;

    pMemorySet(attribs, sizeof *attribs, 0xAB);

    attribs->kind = PFileKind_None;
    attribs->perm = PFilePerm_None;
    attribs->size = 0;

    do {
        status = stat((I8*) name.values, &stats);
    }
    while(status == -1 && errno == EINTR);

    if (status == -1) return 0;

    if (S_ISREG(stats.st_mode) != 0) attribs->kind = PFileKind_Regular;
    if (S_ISDIR(stats.st_mode) != 0) attribs->kind = PFileKind_Directory;

    if (attribs->kind == PFileKind_Regular) {
        attribs->size = stats.st_size;
        attribs->perm |= PFilePerm_Read;
    }

    if (attribs->kind != PFileKind_None) return 1;

    return 0;
}

B32 pLinuxFileDestroy(PString8 name)
{
    return 0;
}

PLinuxFile* pLinuxFileReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PLinuxFile);
}

B32 pLinuxFileOpen(PLinuxFile* self, PString8 name, PFileMode mode)
{
    pMemorySet(self, sizeof *self, 0xAB);

    self->handle = -1;

    Int action = O_CLOEXEC;
    Int access = 0;

    if ((mode & PFileMode_New)    != 0) action |= O_EXCL;
    if ((mode & PFileMode_Always) != 0) action |= O_CREAT;
    if ((mode & PFileMode_Empty)  != 0) action |= O_TRUNC;

    if ((mode & PFileMode_Read)  != 0) access = O_RDONLY;
    if ((mode & PFileMode_Write) != 0) access = O_WRONLY;

    if ((mode & PFileMode_Read) != 0 && (mode & PFileMode_Write) != 0)
        access = O_RDWR;

    if (name.size <= 0 || action == 0) return 0;

    Int handle = open((I8*) name.values, access | action, 0);

    if (handle == -1) return 0;

    self->handle = handle;

    return 1;
}

void pLinuxFileClose(PLinuxFile* self)
{
    int status = 0;

    if (self->handle == -1) return;

    do {
        status = close(self->handle);
    }
    while (status == -1 && errno == EINTR);

    pMemorySet(self, sizeof *self, 0xAB);
}

Int pLinuxFileWrite(PLinuxFile* self, U8* pntr, Int start, Int stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int result = 0;
    Int count  = 0;

    while (result < size) {
        count = write(self->handle, memory + result,
            size - result);

        if (count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

Int pLinuxFileRead(PLinuxFile* self, U8* pntr, Int start, Int stop)
{
    if (pntr == NULL || stop <= start || start < 0) return 0;

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int count  = read(self->handle, memory, size);

    if (count > 0 && count <= size) return count;

    return 0;
}

#endif
