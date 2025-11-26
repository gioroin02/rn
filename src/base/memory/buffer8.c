#ifndef RN_BASE_MEMORY_BUFFER8_C
#define RN_BASE_MEMORY_BUFFER8_C

#include "./buffer8.h"

RnBuffer8
rn_buffer8_make(u8* values, ssize size)
{
    RnBuffer8 result = {0};

    if (values == 0 || size <= 0)
        return result;

    result.values = values;
    result.size   = size;

    return result;
}

RnBuffer8
rn_buffer8_cut(RnBuffer8* self, ssize index, ssize size)
{
    RnBuffer8 result = {0};

    if (size <= 0 || index < 0 || index + size > self->count)
        return result;

    result.values = self->values + index;
    result.size   = size;

    return result;
}

ssize
rn_buffer8_size(RnBuffer8* self)
{
    return self->size;
}

ssize
rn_buffer8_count(RnBuffer8* self)
{
    return self->count;
}

void
rn_buffer8_clear(RnBuffer8* self)
{
    self->count = 0;
}

ssize
rn_buffer8_drop_head(RnBuffer8* self, ssize size)
{
    size = rn_clamp(size, 0, self->count);

    if (size != 0) {
        self->count -= size;

        for (ssize i = 0; i < self->count; i += 1)
            self->values[i] = self->values[i + size];
    }

    return size;
}

ssize
rn_buffer8_insert_head(RnBuffer8* self, u8* values, ssize size)
{
    if (values == 0 || size <= 0 || size > self->size - self->count)
        return 0;

    for (ssize i = self->count; i > 0; i -= 1)
        self->values[i - 1 + size] = self->values[i - 1];

    for (ssize i = 0; i < size; i += 1)
        self->values[i] = values[i];

    self->count += size;

    return size;
}

ssize
rn_buffer8_remove_head(RnBuffer8* self, u8* values, ssize size)
{
    if (values == 0) return 0;

    size = rn_clamp(size, 0, self->count);

    for (ssize i = 0; i < size; i += 1)
        values[i] = self->values[i];

    self->count -= size;

    for (ssize i = 0; i < self->count; i += 1)
        self->values[i] = self->values[i + size];

    return size;
}

ssize
rn_buffer8_drop_tail(RnBuffer8* self, ssize size)
{
    size = rn_clamp(size, 0, self->count);

    if (size != 0)
        self->count -= size;

    return size;
}

ssize
rn_buffer8_insert_tail(RnBuffer8* self, u8* values, ssize size)
{
    if (values == 0 || size <= 0 || size > self->size - self->count)
        return 0;

    for (ssize i = 0; i < size; i += 1)
        self->values[i + self->count] = values[i];

    self->count += size;

    return size;
}

ssize
rn_buffer8_remove_tail(RnBuffer8* self, u8* values, ssize size)
{
    if (values == 0) return 0;

    size = rn_clamp(size, 0, self->count);

    self->count -= size;

    for (ssize i = 0; i < size; i += 1)
        values[i] = self->values[i + self->count];

    return size;
}

#endif // RN_BASE_MEMORY_BUFFER8_C
