#ifndef PX_LINUX_MEMORY_COMMON_H
#define PX_LINUX_MEMORY_COMMON_H

#include "import.h"

ssize
pxLinuxMemoryPageSize();

PxMemoryArena
pxLinuxMemoryReserve(ssize size);

void
pxLinuxMemoryRelease(PxMemoryArena value);

#endif // PX_LINUX_MEMORY_COMMON_H
