#ifndef P_BASE_MEMORY_POOL_H
#define P_BASE_MEMORY_POOL_H

#include "common.h"

#define pMemoryPoolReserveManyOf(self, type, count) \
    ((type*) pMemoryPoolReserve(self, count, sizeof (type)))

#define pMemoryPoolReserveOneOf(self, type) \
    ((type*) pMemoryPoolReserve(self, 1, sizeof (type)))

typedef struct PMemoryPool
{
    U8* pntr_base;
    U8* pntr_next;
    U8* list_head;
    Int size;
    Int stride;
}
PMemoryPool;

PMemoryPool pMemoryPoolMake(void* pntr, Int size, Int stride);

void* pMemoryPoolPntr(PMemoryPool* self);

Int pMemoryPoolSize(PMemoryPool* self);

void pMemoryPoolClear(PMemoryPool* self);

void* pMemoryPoolReserve(PMemoryPool* self, Int count, Int size);

B32 pMemoryPoolRelease(PMemoryPool* self, void* pntr);

#endif
