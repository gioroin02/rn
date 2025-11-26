#ifndef RN_BASE_MEMORY_BUFFER8_H
#define RN_BASE_MEMORY_BUFFER8_H

#include "./arena.h"

typedef struct RnBuffer8
{
    u8*   values;
    ssize size;
    ssize count;
}
RnBuffer8;

RnBuffer8
rn_buffer8_make(u8* values, ssize size);

RnBuffer8
rn_buffer8_cut(RnBuffer8* self, ssize index, ssize size);

ssize
rn_buffer8_size(RnBuffer8* self);

ssize
rn_buffer8_count(RnBuffer8* self);

void
rn_buffer8_clear(RnBuffer8* self);

ssize
rn_buffer_drop_head(RnBuffer8* self, ssize size);

ssize
rn_buffer8_insert_head(RnBuffer8* self, u8* values, ssize size);

ssize
rn_buffer8_remove_head(RnBuffer8* self, u8* values, ssize size);

ssize
rn_buffer_drop_tail(RnBuffer8* self, ssize size);

ssize
rn_buffer8_insert_tail(RnBuffer8* self, u8* values, ssize size);

ssize
rn_buffer8_remove_tail(RnBuffer8* self, u8* values, ssize size);

#endif // RN_BASE_MEMORY_BUFFER8_H
