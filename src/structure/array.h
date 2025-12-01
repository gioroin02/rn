#ifndef RN_STRUCTURE_ARRAY_H
#define RN_STRUCTURE_ARRAY_H

#include "./import.h"

#define RN_ARRAY_TAG struct { ssize size; ssize count; }

#define RnArray(type) struct { RN_ARRAY_TAG arrayTag; type* values; }

#define rnArrayReserve(self, arena, size) ( \
    (self)->values = rnArrayTagReserve(     \
        &(self)->arrayTag,                  \
        (self)->values,                     \
        arena,                              \
        size,                               \
        sizeof(*(self)->values)),           \
    rnArraySize(self)                       \
)

#define rnArraySize(self)           rnArrayTagSize(&(self)->arrayTag)
#define rnArrayCount(self)          rnArrayTagCount(&(self)->arrayTag)
#define rnArrayFront(self)          rnArrayTagFront(&(self)->arrayTag)
#define rnArrayBack(self)           rnArrayTagBack(&(self)->arrayTag)
#define rnArrayIsEmpty(self)        rnArrayTagIsEmpty(&(self)->arrayTag)
#define rnArrayIsFull(self)         rnArrayTagIsFull(&(self)->arrayTag)
#define rnArrayIsIndex(self, index) rnArrayTagIsIndex(&(self)->arrayTag, index)

#define rnArrayInsert(self, index, value) (     \
    rnArrayTagExtend(                           \
        &(self)->arrayTag,                      \
        (self)->values,                         \
        rnEval(index),                          \
        sizeof(*(self)->values)                 \
    ) != 0 ? (                                  \
        (self)->values[rnEval(index)] = value   \
    ), 1                                        \
    :  0                                        \
)

#define rnArrayRemove(self, index, value) (      \
    rnArrayIsIndex(self, rnEval(index)) != 0 ? ( \
        rnArrayTagShrink(                        \
            &(self)->arrayTag,                   \
            (self)->values,                      \
            rnEval(index),                       \
            value,                               \
            sizeof(*(self)->values))             \
    ), 1                                         \
    :  0                                         \
)

#define rnArrayGet(self, index, other) (     \
    rnArrayIsIndex(self, rnEval(index)) != 0 \
    ? ((self)->values[rnEval(index)])        \
    : other                                  \
)

#define rnArrayGetRef(self, index) (         \
    rnArrayIsIndex(self, rnEval(index)) != 0 \
    ? &((self)->values[rnEval(index)])       \
    : 0                                      \
)

void*
rnArrayTagReserve(void* tag, void* values, RnMemoryArena* arena, ssize size, ssize step);

ssize
rnArrayTagSize(void* tag);

ssize
rnArrayTagCount(void* tag);

ssize
rnArrayTagFront(void* tag);

ssize
rnArrayTagBack(void* tag);

b32
rnArrayTagIsEmpty(void* tag);

b32
rnArrayTagIsFull(void* tag);

b32
rnArrayTagIsIndex(void* tag, ssize index);

b32
rnArrayTagExtend(void* tag, void* values, ssize index, ssize step);

b32
rnArrayTagShrink(void* tag, void* values, ssize index, void* value, ssize step);

#endif // RN_STRUCTURE_ARRAY_H
