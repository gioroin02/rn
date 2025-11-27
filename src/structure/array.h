#ifndef RN_STRUCTURE_ARRAY_H
#define RN_STRUCTURE_ARRAY_H

#include "./import.h"

#define RN_ARRAY_TAG struct { ssize size; ssize count; }

#define RnArray(type) { RN_ARRAY_TAG meta; type* values; }

#define rnArraySize(self)           rnMetaArraySize(&(self)->meta)
#define rnArrayCount(self)          rnMetaArrayCount(&(self)->meta)
#define rnArrayFront(self)          rnMetaArrayFront(&(self)->meta)
#define rnArrayBack(self)           rnMetaArrayBack(&(self)->meta)
#define rnArrayIsEmpty(self)        rnMetaArrayIsEmpty(&(self)->meta)
#define rnArrayIsFull(self)         rnMetaArrayIsFull(&(self)->meta)
#define rnArrayIsIndex(self, index) rnMetaArrayIsIndex(&(self)->meta, index)

#define rnArrayInsert(self, index, value) (      \
    rnMetaArrayExtend(                           \
        &(self)->meta,                           \
        (self)->values,                          \
        rnEval(index),                           \
        sizeof(*(self)->values)                  \
    ) != 0 ? (                                   \
        (self)->values[rnEval(index)] = value    \
    ), 1                                         \
    :  0                                         \
)

#define rnArrayRemove(self, index, value) (      \
    rnArrayIsIndex(self, rnEval(index)) != 0 ? ( \
        rnMetaArrayShrink(                       \
            &(self)->meta,                       \
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

ssize
rnMetaArraySize(void* meta);

ssize
rnMetaArrayCount(void* meta);

ssize
rnMetaArrayFront(void* meta);

ssize
rnMetaArrayBack(void* meta);

b32
rnMetaArrayIsEmpty(void* meta);

b32
rnMetaArrayIsFull(void* meta);

b32
rnMetaArrayIsIndex(void* meta, ssize index);

b32
rnMetaArrayExtend(void* meta, void* values, ssize index, ssize step);

b32
rnMetaArrayShrink(void* meta, void* values, ssize index, void* value, ssize step);

#endif // RN_STRUCTURE_ARRAY_H
