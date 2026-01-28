#ifndef P_SYSTEM_WIN32_MEMORY_COMMON_C
#define P_SYSTEM_WIN32_MEMORY_COMMON_C

#include "common.h"

Int pWin32MemoryPageSize()
{
    SYSTEM_INFO info = {0};

    GetSystemInfo(&info);

    return (Int) info.dwPageSize;
}

PMemoryArena pWin32MemoryReserve(Int size)
{
    PMemoryArena result = pMemoryArenaMake(NULL, 0);

    if (size <= 0) return result;

    Int   page   = pWin32MemoryPageSize();
    void* memory = NULL;

    size = pMemoryAlignSize(size, page);

    memory = VirtualAlloc(0, size,
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (memory == NULL) return result;

    return pMemoryArenaMake(memory, size);
}

B32 pWin32MemoryRelease(PMemoryArena* arena)
{
    Int   page   = pWin32MemoryPageSize();
    void* memory = pMemoryArenaPntr(arena);
    Int   size   = pMemoryArenaSize(arena);

    if (memory == NULL || size <= 0 || size % page != 0)
        return 0;

    VirtualFree(arena, 0, MEM_RELEASE);

    pMemorySet(arena, sizeof *arena, 0xAB);

    return 1;
}

#endif
