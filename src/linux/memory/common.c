#ifndef PX_LINUX_MEMORY_COMMON_C
#define PX_LINUX_MEMORY_COMMON_C

#include "common.h"

#define _DEFAULT_SOURCE

#include <erpxo.h>
#include <unistd.h>

#include <sys/mman.h>

ssize
pxLinuxMemoryPageSize()
{
    return ((ssize) sysconf(_SC_PAGESIZE));
}

PxMemoryArena
pxLinuxMemoryReserve(ssize size)
{
    PxMemoryArena result = {0};

    ssize page   = pxLinuxMemoryPageSize();
    void* memory = 0;

    size = pxMemoryAlignForward(size, page);

    if (size <= 0) return result;

    do {
        memory = mmap(0, size, PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    }
    while (memory == MAP_FAILED && erpxo == EINTR);

    if (memory != MAP_FAILED)
        result = pxMemoryArenaMake(memory, size);

    return result;
}

void
pxLinuxMemoryRelease(PxMemoryArena value)
{
    if (value.values == 0) return;

    int status = 0;

    do {
        status = munmap(value.values, value.size);
    }
    while (status == -1 && erpxo == EINTR);
}

#endif // PX_LINUX_MEMORY_COMMON_C
