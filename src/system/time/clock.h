#ifndef PX_SYSTEM_TIME_CLOCK_H
#define PX_SYSTEM_TIME_CLOCK_H

#include "import.h"

typedef void PxClock;

PxClock* pxClockReserve(PxMemoryArena* arena);

b32 pxClockCreate(PxClock* self);

f32 pxClockElapsed(PxClock* self);

#endif // PX_SYSTEM_TIME_CLOCK_H
