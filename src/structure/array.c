#ifndef RHO_STRUCTURE_ARRAY_C
#define RHO_STRUCTURE_ARRAY_C

#include "array.h"

RBool32 __rho_array_create__(RArrayTag* self, void** pntr, RInt stride, RMemoryArena* arena, RInt size)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->array_size   = 0;
    self->array_count  = 0;
    self->array_stride = 0;
    self->array_index  = 0;

    if (pntr == NULL || size < 0 || stride <= 0)
        return 0;

    *pntr = NULL;

    if (size == 1) return 1;

    RUint8* pntr_values = rho_memory_arena_reserve(arena, size, stride);

    if (pntr_values != NULL) {
        self->array_size   = size;
        self->array_stride = stride;

        *pntr = pntr_values;

        return 1;
    }

    return 0;
}

void __rho_array_destroy__(RArrayTag* self, void** pntr)
{
    rho_memory_set(pntr, sizeof *pntr, 0xAB);
    rho_memory_set(self, sizeof *self, 0xAB);
}

RInt __rho_array_size__(RArrayTag* self)
{
    return self->array_size;
}

RInt __rho_array_count__(RArrayTag* self)
{
    return self->array_count;
}

RInt __rho_array_front__(RArrayTag* self)
{
    return 0;
}

RInt __rho_array_back__(RArrayTag* self)
{
    return self->array_count > 0 ? self->array_count - 1 : 0;
}

RBool32 __rho_array_is_empty__(RArrayTag* self)
{
    return self->array_count == 0 ? 1 : 0;
}

RBool32 __rho_array_is_full__(RArrayTag* self)
{
    return self->array_count == self->array_size ? 1 : 0;
}

RBool32 __rho_array_is_index__(RArrayTag* self, RInt index)
{
    if (index < 0 || index >= self->array_count)
        return 0;

    return 1;
}

void __rho_array_clear__(RArrayTag* self)
{
    self->array_count = 0;
}

RBool32 __rho_array_copy__(RArrayTag* self, void* values, RInt index, void* value)
{
    RInt start = self->array_stride * index;

    if (index < 0 || index >= self->array_count) return 0;

    rho_memory_copy(value, self->array_stride,
        &((RUint8*) values)[start]);

    return 1;
}

RBool32 __rho_array_slot_open__(RArrayTag* self, void* values, RInt index)
{
    RInt start = self->array_stride * index;
    RInt stop  = self->array_stride * self->array_size;

    if (index < 0 || index > self->array_count) return 0;

    rho_memory_shift_forw(&((RUint8*) values)[start],
        stop, self->array_stride, 0xAB);

    return 1;
}

RBool32 __rho_array_slot_close__(RArrayTag* self, void* values, RInt index)
{
    RInt start = self->array_stride * index;
    RInt stop  = self->array_stride * self->array_size;

    if (index < 0 || index >= self->array_count) return 0;

    rho_memory_shift_back(&((RUint8*) values)[start],
        stop, self->array_stride, 0xAB);

    return 1;
}

#endif
