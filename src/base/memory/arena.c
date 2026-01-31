#ifndef RHO_BASE_MEMORY_ARENA_C
#define RHO_BASE_MEMORY_ARENA_C

#include "arena.h"

RMemoryArena rho_memory_arena_make(void* pntr, RInt size)
{
    RMemoryArena result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.pntr_base = NULL;
    result.pntr_next = NULL;
    result.size      = 0;

    if (pntr != NULL || size > 0) {
        result.pntr_base = (RUint8*) pntr;
        result.pntr_next = result.pntr_base;
        result.size      = size;

        rho_memory_set(result.pntr_base, result.size, 0xAB);
    }

    return result;
}

void* rho_memory_arena_pntr(RMemoryArena* self)
{
    return self->pntr_base;
}

RInt rho_memory_arena_size(RMemoryArena* self)
{
    return self->size;
}

void rho_memory_arena_clear(RMemoryArena* self)
{
    rho_memory_set(self->pntr_base, self->size, 0xAB);

    self->pntr_next = self->pntr_base;
}

void* rho_memory_arena_reserve(RMemoryArena* self, RInt count, RInt size)
{
    if (count <= 0 || size <= 0 || count > RHO_INT_MAX / size)
        return NULL;

    RInt    bytes  = count * size;
    RUint8* result = self->pntr_next;
    RUint8* next   = self->pntr_next + bytes;

    if (next < self->pntr_base || next > self->pntr_base + self->size)
        return NULL;

    self->pntr_next = rho_memory_align_pntr(next, RHO_MEMORY_ALIGNMENT);

    rho_memory_set(result, self->pntr_next - result, 0xAB);

    return result;
}

RBool32 rho_memory_arena_release(RMemoryArena* arena, void* pntr)
{
    return 0;
}

RBool32 rho_memory_arena_rewind(RMemoryArena* self, void* pntr)
{
    if (pntr == NULL) return 0;

    RUint8* head = ((RUint8*) pntr);
    RInt    dist = head - self->pntr_base;

    if (head < self->pntr_base || head >= self->pntr_next)
        return 0;

    if (dist % RHO_MEMORY_ALIGNMENT != 0) return 0;

    self->pntr_next = self->pntr_base + dist;

    rho_memory_set(self->pntr_base + dist, self->size - dist, 0xAB);

    return 1;
}

void* rho_memory_arena_tell(RMemoryArena* self)
{
    return self->pntr_next;
}

#endif
