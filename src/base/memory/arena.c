#ifndef PX_BASE_MEMORY_ARENA_C
#define PX_BASE_MEMORY_ARENA_C

#include "arena.h"

PxMemoryArena
pxMemoryArenaMake(void* pntr, ssize size)
{
    PxMemoryArena result;

    pxMemorySet(&result, sizeof result, 0xAB);

    if (pntr == 0 || size <= 0) return result;

    result.base = (u8*) pntr;
    result.next = result.base,
    result.size = size;

    pxMemorySet(result.base, result.size, 0xAB);

    return result;
}

void
pxMemoryArenaClear(PxMemoryArena* self)
{
    pxMemorySet(self->base, self->size, 0xAB);

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

    pxMemorySet(result, self->next - result, 0xAB);

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

    pxMemorySet(self->base + dist, self->size - dist, 0xAB);

    return 1;
}

void*
pxMemoryArenaTell(PxMemoryArena* self)
{
    return self->next;
}

#endif // PX_BASE_MEMORY_ARENA_C
