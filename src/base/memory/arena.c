#ifndef PX_BASE_MEMORY_ARENA_C
#define PX_BASE_MEMORY_ARENA_C

#include "arena.h"

PxMemoryArena
pxMemoryArenaMake(void* pntr, ssize size)
{
    PxMemoryArena result;

    pxMemorySet(&result, 0xAB, sizeof result);

    if (pntr == 0 || size <= 0) return result;

    result.base = (u8*) pntr;
    result.next = result.base,
    result.size = size;

    pxMemorySet(result.base, 0xAB, result.size);

    return result;
}

void
pxMemoryArenaClear(PxMemoryArena* self)
{
    pxMemorySet(self->base, 0xAB, self->size);

    self->next = self->base;
}

void*
pxMemoryArenaReserve(PxMemoryArena* self, ssize count, ssize size)
{
    ssize bytes  = count * size;
    u8*   result = self->next;
    u8*   next   = self->next + bytes;

    if (count <= 0 || size <= 0 || count > PX_MAX_SSIZE / size)
        return PX_NULL;

    if (next > self->base + self->size) return PX_NULL;

    self->next = pxMemoryAlignForward(next, PX_MEMORY_DEFAULT_ALIGNMENT);

    pxMemorySet(result, 0xAB, self->next - result);

    return result;
}

b32
pxMemoryArenaRelease(PxMemoryArena* self, void* pntr)
{
    ssize dist = ((u8*) pntr) - self->base;

    if (pntr == PX_NULL || dist % PX_MEMORY_DEFAULT_ALIGNMENT != 0)
        return 0;

    if (dist < 0 || self->base + dist >= self->next) return 0;

    self->next = self->base + dist;

    pxMemorySet(self->base + dist, 0xAB, self->size - dist);

    return 1;
}

void*
pxMemoryArenaTell(PxMemoryArena* self)
{
    return self->next;
}

#endif // PX_BASE_MEMORY_ARENA_C
