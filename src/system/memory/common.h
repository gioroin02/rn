#ifndef RN_SYSTEM_MEMORY_COMMON_H
#define RN_SYSTEM_MEMORY_COMMON_H

#include "./import.h"

b32
rnSystemMemoryStart();

void
rnSystemMemoryStop();

ssize
rnSystemMemoryPageSize();

RnMemoryArena
rnSystemMemoryReserve(ssize size);

void
rnSystemMemoryRelease(RnMemoryArena value);

#endif // RN_SYSTEM_MEMORY_COMMON_H
