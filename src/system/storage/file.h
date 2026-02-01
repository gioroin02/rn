#ifndef RHO_SYSTEM_STORAGE_FILE_H
#define RHO_SYSTEM_STORAGE_FILE_H

#include "import.h"

typedef enum RFileKind
{
    RFileKind_None,
    RFileKind_Regular,
    RFileKind_Directory,
}
RFileKind;

typedef enum RFilePerm
{
    RFilePerm_None  = 0,
    RFilePerm_Read  = 1 << 0,
    RFilePerm_Write = 1 << 1,
}
RFilePerm;

typedef enum RFileMode
{
    RFileMode_None   = 0,
    RFileMode_Read   = 1 << 0,
    RFileMode_Write  = 1 << 1,
    RFileMode_New    = 1 << 2,
    RFileMode_Always = 1 << 3,
    RFileMode_Empty  = 1 << 4,
}
RFileMode;

typedef struct RFileAttribs
{
    RFileKind kind;
    RFilePerm perm;

    RInt size;
}
RFileAttribs;

typedef struct RFile { RUint8 __private__; } RFile;

RBool32 rho_file_find(RString8 name, RFileAttribs* attribs);

RBool32 rho_file_delete(RString8 name);

RFile* rho_file_reserve(RMemoryArena* arena);

RBool32 rho_file_open(RFile* self, RString8 name, RFileMode mode);

void rho_file_close(RFile* self);

RInt rho_file_write(RFile* self, RUint8* pntr, RInt start, RInt stop);

RInt rho_file_read(RFile* self, RUint8* pntr, RInt start, RInt stop);

#endif
