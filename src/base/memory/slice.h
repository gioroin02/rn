#ifndef RN_BASE_MEMORY_SLICE_H
#define RN_BASE_MEMORY_SLICE_H

#include "./common.h"

#define rn_slice_cut(memory, start, stop) rn_memory_slice_make(memory, \
    rn_max(start, 0), rn_min(stop, rn_array_count(memory)), rn_array_stride(memory))

#define rn_slice(memory) rn_slice_cut(memory, 0, rn_array_count(memory))

typedef struct RnMemorySlice
{
    u8*   values;
    ssize size;
    ssize step;
}
RnMemorySlice;

RnMemorySlice
rn_memory_slice_make(void* memory, ssize start, ssize stop, ssize step);

ssize
rn_memory_slice_size(RnMemorySlice self);

ssize
rn_memory_slice_step(RnMemorySlice self);

ssize
rn_memory_slice_bytes(RnMemorySlice self);

void*
rn_memory_slice_zero(RnMemorySlice self);

void*
rn_memory_slice_flip(RnMemorySlice self);

void*
rn_memory_slice_swap(RnMemorySlice self, ssize index, ssize other);

#endif // RN_BASE_MEMORY_SLICE_H
