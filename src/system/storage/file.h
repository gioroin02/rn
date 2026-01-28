#ifndef P_SYSTEM_STORAGE_FILE_H
#define P_SYSTEM_STORAGE_FILE_H

#include "import.h"

typedef enum PFileKind
{
    PFileKind_None,
    PFileKind_Regular,
    PFileKind_Directory,
}
PFileKind;

typedef enum PFilePerm
{
    PFilePerm_None  = 0,
    PFilePerm_Read  = 1 << 0,
    PFilePerm_Write = 1 << 1,
}
PFilePerm;

typedef enum PFileMode
{
    PFileMode_None   = 0,
    PFileMode_Read   = 1 << 0,
    PFileMode_Write  = 1 << 1,
    PFileMode_New    = 1 << 2,
    PFileMode_Always = 1 << 3,
    PFileMode_Empty  = 1 << 4,
}
PFileMode;

typedef struct PFileAttribs
{
    PFileKind kind;
    PFilePerm perm;

    Int size;
}
PFileAttribs;

typedef struct PFile { U8 __private__; } PFile;

B32 pFileAttribs(PString8 name, PFileAttribs* attribs);

B32 pFileDestroy(PString8 name);

PFile* pFileReserve(PMemoryArena* arena);

B32 pFileOpen(PFile* self, PString8 name, PFileMode mode);

void pFileClose(PFile* self);

Int pFileWrite(PFile* self, U8* pntr, Int start, Int stop);

Int pFileRead(PFile* self, U8* pntr, Int start, Int stop);

#endif
