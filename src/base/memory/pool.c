#ifndef PX_BASE_MEMORY_POOL_C
#define PX_BASE_MEMORY_POOL_C

#include "pool.h"

typedef struct PxMemoryPoolNode
{
    struct PxMemoryPoolNode* next;
}
PxMemoryPoolNode;

PxMemoryPool
pxMemoryPoolMake(void* pntr, ssize size, ssize step)
{
    PxMemoryPool result;

    pxMemorySet(&result, sizeof result, 0xAB);

    if (pntr == 0 || size <= 0 || step <= 0) return result;

    result.base = (u8*) pntr;
    result.next = result.base;
    result.head = PX_NULL;
    result.size = size;
    result.step = pxMax(step, PX_MEMORY_DEFAULT_ALIGNMENT);

    pxMemorySet(result.base, result.size, 0xAB);

    return result;
}

void
pxMemoryPoolClear(PxMemoryPool* self)
{
    pxMemorySet(self->base, self->size, 0xAB);

    self->next = self->base;
    self->head = PX_NULL;
}

void*
pxMemoryPoolReserve(PxMemoryPool* self, ssize count, ssize size)
{
    ssize bytes  = count * size;
    u8*   result = self->head;
    u8*   next   = self->next + bytes;

    if (count <= 0 || size <= 0 || count > PX_MAX_SSIZE / size)
        return PX_NULL;

    if (bytes > self->step) return PX_NULL;

    if (self->head == PX_NULL) {
        if (next > self->base + self->size) return PX_NULL;

        result     = self->next;
        self->next = pxMemoryAlignForward(next, PX_MEMORY_DEFAULT_ALIGNMENT);
    }
    else self->head = ((PxMemoryPoolNode*) result)->next;

    pxMemorySet(result, self->step, 0xAB);

    return result;
}

b32
pxMemoryPoolRelease(PxMemoryPool* self, void* pntr)
{
    ssize dist = ((u8*) pntr) - self->base;

    if (pntr == PX_NULL || dist % PX_MEMORY_DEFAULT_ALIGNMENT != 0)
        return 0;

    if (dist < 0 || self->base + dist >= self->next) return 0;

    pxMemorySet(pntr, self->step, 0xAB);

    PxMemoryPoolNode* node = (PxMemoryPoolNode*) pntr;

    node->next = self->head;
    self->head = node;

    return 1;
}

#endif // PX_BASE_MEMORY_POOL_C
