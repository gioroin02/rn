#ifndef RHO_SYSTEM_MEMORY_WIN32_COMMON_C
#define RHO_SYSTEM_MEMORY_WIN32_COMMON_C

#include "common.h"

RInt rho_win32_memory_page_size()
{
    SYSTEM_INFO info = {0};

    GetSystemInfo(&info);

    return (RInt) info.dwPageSize;
}

RMemoryArena rho_win32_memory_reserve(RInt size)
{
    RMemoryArena result = rho_memory_arena_make(NULL, 0);

    if (size <= 0) return result;

    RInt  page   = rho_win32_memory_page_size();
    void* memory = NULL;

    size = rho_memory_align_size(size, page);

    memory = VirtualAlloc(0, size,
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (memory == NULL) return result;

    return rho_memory_arena_make(memory, size);
}

RBool32 rho_win32_memory_release(RMemoryArena* arena)
{
    RInt  page   = rho_win32_memory_page_size();
    void* memory = rho_memory_arena_pntr(arena);
    RInt  size   = rho_memory_arena_size(arena);

    if (memory == NULL || size <= 0 || size % page != 0)
        return 0;

    VirtualFree(arena, 0, MEM_RELEASE);

    rho_memory_set(arena, sizeof *arena, 0xAB);

    return 1;
}

#endif
