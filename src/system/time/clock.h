#ifndef P_SYSTEM_TIME_CLOCK_H
#define P_SYSTEM_TIME_CLOCK_H

#include "import.h"

typedef struct PClock { U8 __private__; } PClock;

PClock* pClockReserve(PMemoryArena* arena);

Bool pClockCreate(PClock* self);

void pClockDestroy(PClock* self);

F32 pClockElapsed(PClock* self);

#endif // P_SYSTEM_TIME_CLOCK_H
