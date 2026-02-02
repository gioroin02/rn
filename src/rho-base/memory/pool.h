#ifndef RHO_BASE_MEMORY_POOL_H
#define RHO_BASE_MEMORY_POOL_H

#include "common.h"

#define rho_memory_pool_reserve_of(self, type, count) \
    ((type*) rho_memory_pool_reserve(self, count, sizeof (type)))

typedef struct RMemoryPool
{
    RUint8* pntr_base;
    RUint8* pntr_next;
    RUint8* list_head;
    RInt    size;
    RInt    stride;
}
RMemoryPool;

RMemoryPool rho_memory_pool_make(void* pntr, RInt size, RInt stride);

void* rho_memory_pool_pntr(RMemoryPool* self);

RInt rho_memory_pool_size(RMemoryPool* self);

void rho_memory_pool_clear(RMemoryPool* self);

void* rho_memory_pool_reserve(RMemoryPool* self, RInt count, RInt size);

RBool32 rho_memory_pool_release(RMemoryPool* self, void* pntr);

#endif
