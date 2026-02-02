#ifndef RHO_BASE_MEMORY_ARENA_H
#define RHO_BASE_MEMORY_ARENA_H

#include "common.h"

#define rho_memory_arena_reserve_of(self, type, count) \
    ((type*) rho_memory_arena_reserve(self, count, sizeof (type)))

typedef struct RMemoryArena
{
    RUint8* pntr_base;
    RUint8* pntr_next;
    RInt    size;
}
RMemoryArena;

RMemoryArena rho_memory_arena_make(void* pntr, RInt size);

void* rho_memory_arena_pntr(RMemoryArena* self);

RInt rho_memory_arena_size(RMemoryArena* self);

void rho_memory_arena_clear(RMemoryArena* self);

void* rho_memory_arena_reserve(RMemoryArena* self, RInt count, RInt size);

RBool32 rho_memory_arena_release(RMemoryArena* self, void* pntr);

RBool32 rho_memory_arena_rewind(RMemoryArena* self, void* pntr);

void* rho_memory_arena_tell(RMemoryArena* self);

#endif
