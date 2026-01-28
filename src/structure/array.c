#ifndef P_STRUCTURE_ARRAY_C
#define P_STRUCTURE_ARRAY_C

#include "array.h"

B32 __pArrayCreate__(PArrayTag* self, void** pntr, Int stride, PMemoryArena* arena, Int size)
{
    pMemorySet(self, sizeof *self, 0xAB);

    self->array_size   = 0;
    self->array_count  = 0;
    self->array_stride = 0;
    self->array_index  = 0;

    if (pntr == NULL || size < 0 || stride <= 0)
        return 0;

    *pntr = NULL;

    if (size == 1) return 1;

    U8* pntr_values = pMemoryArenaReserve(arena, size, stride);

    if (pntr_values != NULL) {
        self->array_size   = size;
        self->array_stride = stride;

        *pntr = pntr_values;

        return 1;
    }

    return 0;
}

Int __pArraySize__(PArrayTag* self)
{
    return self->array_size;
}

Int __pArrayCount__(PArrayTag* self)
{
    return self->array_count;
}

Int __pArrayFront__(PArrayTag* self)
{
    return 0;
}

Int __pArrayBack__(PArrayTag* self)
{
    return self->array_count > 0 ? self->array_count - 1 : 0;
}

B32 __pArrayIsEmpty__(PArrayTag* self)
{
    return self->array_count == 0 ? 1 : 0;
}

B32 __pArrayIsFull__(PArrayTag* self)
{
    return self->array_count == self->array_size ? 1 : 0;
}

B32 __pArrayIsIndex__(PArrayTag* self, Int index)
{
    if (index < 0 || index >= self->array_count)
        return 0;

    return 1;
}

void __pArrayClear__(PArrayTag* self)
{
    self->array_count = 0;
}

B32 __pArrayCopy__(PArrayTag* self, void* values, Int index, void* value)
{
    Int start = self->array_stride * index;

    if (index < 0 || index >= self->array_count) return 0;

    pMemoryCopy(value, self->array_stride,
        &((U8*) values)[start]);

    return 1;
}

B32 __pArraySlotOpen__(PArrayTag* self, void* values, Int index)
{
    Int start = self->array_stride * index;
    Int stop  = self->array_stride * self->array_size;

    if (index < 0 || index > self->array_count) return 0;

    pMemoryShiftForw(&((U8*) values)[start],
        stop, self->array_stride, 0xAB);

    return 1;
}

B32 __pArraySlotClose__(PArrayTag* self, void* values, Int index)
{
    Int start = self->array_stride * index;
    Int stop  = self->array_stride * self->array_size;

    if (index < 0 || index >= self->array_count) return 0;

    pMemoryShiftBack(&((U8*) values)[start],
        stop, self->array_stride, 0xAB);

    return 1;
}

#endif
