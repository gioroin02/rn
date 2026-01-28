#ifndef P_SYSTEM_LINUX_MEMORY_COMMON_H
#define P_SYSTEM_LINUX_MEMORY_COMMON_H

#include "import.h"

#ifndef _DEFAULT_SOURCE

    #define _DEFAULT_SOURCE

#endif

#include <unistd.h>
#include <errno.h>

#include <sys/mman.h>

Int pLinuxMemoryPageSize();

PMemoryArena pLinuxMemoryReserve(Int size);

B32 pLinuxMemoryRelease(PMemoryArena* arena);

#endif
