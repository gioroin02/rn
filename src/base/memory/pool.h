#ifndef PX_BASE_MEMORY_POOL_H
#define PX_BASE_MEMORY_POOL_H

#include "common.h"

#define pxMemoryPoolReserveOneOf(self, type) \
    ((type*) pxMemoryPoolReserve(self, 1, sizeof (type)))

typedef struct PxMemoryPool
{
    u8*   base;
    u8*   next;
    void* head;
    ssize size;
    ssize step;
}
PxMemoryPool;

PxMemoryPool
pxMemoryPoolMake(void* pntr, ssize size, ssize step);

void
pxMemoryPoolClear(PxMemoryPool* self);

void*
pxMemoryPoolReserve(PxMemoryPool* self, ssize count, ssize size);

b32
pxMemoryPoolRelease(PxMemoryPool* self, void* pntr);

#endif // PX_BASE_MEMORY_POOL_H
