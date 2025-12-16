#ifndef PX_WIN32_MEMORY_COMMON_C
#define PX_WIN32_MEMORY_COMMON_C

#include "common.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

ssize
pxWin32MemoryPageSize()
{
    SYSTEM_INFO info = {0};

    GetSystemInfo(&info);

    return ((ssize) info.dwPageSize);
}

PxMemoryArena
pxWin32MemoryReserve(ssize size)
{
    PxMemoryArena result = {0};

    ssize page   = pxWin32MemoryPageSize();
    void* memory = 0;

    size = pxMemoryAlignForward(size, page);

    if (size <= 0) return result;

    memory = VirtualAlloc(0, size,
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (memory != 0)
        result = pxMemoryArenaMake(memory, size);

    return result;
}

void
pxWin32MemoryRelease(PxMemoryArena value)
{
    if (value.values != 0)
        VirtualFree(value.values, 0, MEM_RELEASE);
}

#endif // PX_WIN32_MEMORY_COMMON_C
