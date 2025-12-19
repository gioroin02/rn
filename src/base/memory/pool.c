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

    result.pntr_base = (u8*) pntr;
    result.pntr_next = result.pntr_base;
    result.list_head = PX_NULL;
    result.size      = size;
    result.step      = pxMax(step, PX_MEMORY_DEFAULT_ALIGNMENT);

    pxMemorySet(result.pntr_base, result.size, 0xAB);

    return result;
}

void
pxMemoryPoolClear(PxMemoryPool* self)
{
    pxMemorySet(self->pntr_base, self->size, 0xAB);

    self->pntr_next = self->pntr_base;
    self->list_head = PX_NULL;
}

void*
pxMemoryPoolReserve(PxMemoryPool* self, ssize count, ssize size)
{
    ssize bytes  = count * size;
    u8*   result = self->list_head;
    u8*   next   = self->pntr_next + bytes;

    if (count <= 0 || size <= 0 || count > PX_MAX_SSIZE / size)
        return PX_NULL;

    if (bytes > self->step) return PX_NULL;

    if (self->list_head == PX_NULL) {
        if (next > self->pntr_base + self->size) return PX_NULL;

        result = self->pntr_next;

        self->pntr_next =
            pxMemoryAlignForward(next, PX_MEMORY_DEFAULT_ALIGNMENT);
    }
    else self->list_head = ((PxMemoryPoolNode*) result)->next;

    pxMemorySet(result, self->step, 0xAB);

    return result;
}

b32
pxMemoryPoolRelease(PxMemoryPool* self, void* pntr)
{
    ssize dist = ((u8*) pntr) - self->pntr_base;

    if (pntr == PX_NULL || dist % PX_MEMORY_DEFAULT_ALIGNMENT != 0)
        return 0;

    if (dist < 0 || self->pntr_base + dist >= self->pntr_next) return 0;

    pxMemorySet(pntr, self->step, 0xAB);

    PxMemoryPoolNode* node = (PxMemoryPoolNode*) pntr;

    node->next      = self->list_head;
    self->list_head = node;

    return 1;
}

#endif // PX_BASE_MEMORY_POOL_C
