#ifndef RHO_BASE_MEMORY_POOL_C
#define RHO_BASE_MEMORY_POOL_C

#include "pool.h"

#define RHO_MEMORY_POOL_NODE_SIZE ((RInt) sizeof (RMemoryPoolNode))

typedef enum RMemoryPoolFlag
{
    RMemoryPoolFlag_None = 0,
    RMemoryPoolFlag_Free = 1 << 0,
}
RMemoryPoolFlag;

typedef struct RMemoryPoolNode RMemoryPoolNode;

struct RMemoryPoolNode
{
    RMemoryPoolFlag  flag;
    RMemoryPoolNode* list_next;
};

RMemoryPool rho_memory_pool_make(void* pntr, RInt size, RInt stride)
{
    RMemoryPool result = {0};

    rho_memory_set(&result, sizeof result, 0xAB);

    result.pntr_base = NULL;
    result.pntr_next = NULL;
    result.list_head = NULL;
    result.size      = 0;

    if (pntr != NULL || size > 0 || stride > 0) {
        result.pntr_base = (RUint8*) pntr;
        result.pntr_next = result.pntr_base;
        result.size      = size;
        result.stride    = rho_memory_align_size(stride, RHO_MEMORY_ALIGNMENT);

        rho_memory_set(result.pntr_base, result.size, 0xAB);
    }

    return result;
}

void* rho_memory_pool_pntr(RMemoryPool* self)
{
    return self->pntr_base;
}

RInt rho_memory_pool_size(RMemoryPool* self)
{
    return self->size;
}

void rho_memory_pool_clear(RMemoryPool* self)
{
    rho_memory_set(self->pntr_base, self->size, 0xAB);

    self->pntr_next = self->pntr_base;
    self->list_head = NULL;
}

void* rho_memory_pool_reserve(RMemoryPool* self, RInt count, RInt size)
{
    if (count <= 0 || size <= 0 || count > RHO_INT_MAX / size)
        return NULL;

    RInt size_header = rho_memory_align_size(
        RHO_MEMORY_POOL_NODE_SIZE, RHO_MEMORY_ALIGNMENT);

    RMemoryPoolNode* node  = (RMemoryPoolNode*) self->list_head;
    RInt             bytes = count * size;

    if (bytes < 0 || bytes > self->stride) return NULL;

    if (node == NULL) {
        RUint8* next = ((RUint8*) self->pntr_next) + size_header + self->stride;

        if (next < self->pntr_base || next > self->pntr_base + self->size)
            return NULL;

        node = (RMemoryPoolNode*) self->pntr_next;

        self->pntr_next = next;
    }
    else self->list_head = (RUint8*) node->list_next;

    rho_memory_set(node, size_header + self->stride, 0xAB);

    node->flag      = RMemoryPoolFlag_None;
    node->list_next = NULL;

    return ((RUint8*) node) + size_header;
}

RBool32 rho_memory_pool_release(RMemoryPool* self, void* pntr)
{
    RInt size_header = rho_memory_align_size(
        RHO_MEMORY_POOL_NODE_SIZE, RHO_MEMORY_ALIGNMENT);

    if (pntr == NULL) return 0;

    RUint8* head = ((RUint8*) pntr) - size_header;
    RInt    dist = head - self->pntr_base;

    if (head < self->pntr_base || head >= self->pntr_next)
        return 0;

    if (dist % (size_header + self->stride) != 0) return 0;

    RMemoryPoolNode* node = (RMemoryPoolNode*) head;

    if ((node->flag & RMemoryPoolFlag_Free) != 0) return 0;

    rho_memory_set(head, size_header + self->stride, 0xAB);

    node->flag      = RMemoryPoolFlag_Free;
    node->list_next = (RMemoryPoolNode*) self->list_head;
    self->list_head = (RUint8*) node;

    return 1;
}

#endif
