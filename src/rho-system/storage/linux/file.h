#ifndef RHO_SYSTEM_LINUX_STORAGE_FILE_H
#define RHO_SYSTEM_LINUX_STORAGE_FILE_H

#include "import.h"

#ifndef _DEFAULT_SOURCE

    #define _DEFAULT_SOURCE

#endif

#include <unistd.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct stat RLinuxFileStat;

typedef struct RLinuxFile
{
    RInt handle;
}
RLinuxFile;

RBool32 rho_linux_file_find(RString8 name, RFileAttribs* attribs);

RBool32 rho_linux_file_delete(RString8 name);

RLinuxFile* rho_linux_file_reserve(RMemoryArena* arena);

RBool32 rho_linux_file_open(RLinuxFile* self, RString8 name, RFileMode mode);

void rho_linux_file_close(RLinuxFile* self);

RInt rho_linux_file_write(RLinuxFile* self, RUint8* pntr, RInt start, RInt stop);

RInt rho_linux_file_read(RLinuxFile* self, RUint8* pntr, RInt start, RInt stop);

#endif
