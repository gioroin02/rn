#ifndef P_SYSTEM_LINUX_STORAGE_FILE_H
#define P_SYSTEM_LINUX_STORAGE_FILE_H

#include "import.h"

#ifndef _DEFAULT_SOURCE

    #define _DEFAULT_SOURCE

#endif

#include <unistd.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct stat PLinuxFileStat;

typedef struct PLinuxFile
{
    Int handle;
}
PLinuxFile;

B32 pLinuxFileAttribs(PString8 name, PFileAttribs* attribs);

B32 pLinuxFileDestroy(PString8 name);

PLinuxFile* pLinuxFileReserve(PMemoryArena* arena);

B32 pLinuxFileOpen(PLinuxFile* self, PString8 name, PFileMode mode);

void pLinuxFileClose(PLinuxFile* self);

Int pLinuxFileWrite(PLinuxFile* self, U8* pntr, Int start, Int stop);

Int pLinuxFileRead(PLinuxFile* self, U8* pntr, Int start, Int stop);

#endif
