#ifndef RN_BASE_MEMORY_SLICE_H
#define RN_BASE_MEMORY_SLICE_H

#include "./common.h"

#define rnSlice(memory) \
    rnMemorySliceMake(memory, 0, rnManySize(memory), rnManyStep(memory))

#define rnSliceCut(memory, start, stop) \
    rnMemorySliceMake(memory, rnMax(start, 0), rnMin(stop, rnManySize(memory)), rnManyStep(memory))

typedef struct RnMemorySlice
{
    u8*   values;
    ssize size;
    ssize step;
}
RnMemorySlice;

RnMemorySlice
rnMemorySliceMake(void* memory, ssize start, ssize stop, ssize step);

ssize
rnMemorySliceSize(RnMemorySlice self);

ssize
rnMemorySliceStep(RnMemorySlice self);

ssize
rnMemorySliceBytes(RnMemorySlice self);

void*
rnMemorySliceZero(RnMemorySlice self);

void*
rnMemorySliceFlip(RnMemorySlice self);

void*
rnMemorySliceSwap(RnMemorySlice self, ssize index, ssize other);

#endif // RN_BASE_MEMORY_SLICE_H
