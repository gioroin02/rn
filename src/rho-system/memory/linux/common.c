#ifndef RHO_SYSTEM_MEMORY_LINUX_COMMON_C
#define RHO_SYSTEM_MEMORY_LINUX_COMMON_C

#include "common.h"

RInt rho_linux_memory_page_size()
{
    return (RInt) sysconf(_SC_PAGESIZE);
}

RMemoryArena rho_linux_memory_reserve(RInt size)
{
    RMemoryArena result = rho_memory_arena_make(NULL, 0);

    if (size <= 0) return result;

    RInt  page   = rho_linux_memory_page_size();
    void* memory = NULL;

    size = rho_memory_align_size(size, page);

    do {
        memory = mmap(0, size, PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    }
    while (memory == MAP_FAILED && errno == EINTR);

    if (memory == MAP_FAILED) return result;

    return rho_memory_arena_make(memory, size);
}

RBool32 rho_linux_memory_release(RMemoryArena* arena)
{
    int   status = 0;
    RInt  page   = rho_linux_memory_page_size();
    void* memory = rho_memory_arena_pntr(arena);
    RInt  size   = rho_memory_arena_size(arena);

    if (memory == NULL || size <= 0 || size % page != 0)
        return 0;

    do {
        status = munmap(memory, size);
    }
    while (status == -1 && errno == EINTR);

    rho_memory_set(arena, sizeof *arena, 0xAB);

    return 1;
}

#endif
