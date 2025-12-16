#ifndef PX_WIN32_MEMORY_COMMON_H
#define PX_WIN32_MEMORY_COMMON_H

#include "import.h"

ssize
pxWin32MemoryPageSize();

PxMemoryArena
pxWin32MemoryReserve(ssize size);

void
pxWin32MemoryRelease(PxMemoryArena value);

#endif // PX_WIN32_MEMORY_COMMON_H
