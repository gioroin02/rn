#ifndef PX_WIN32_TIME_CLOCK_H
#define PX_WIN32_TIME_CLOCK_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

typedef struct PxWin32Clock
{
    LARGE_INTEGER frequency;

    LARGE_INTEGER tick_previous;
    LARGE_INTEGER tick_current;
}
PxWin32Clock;

PxWin32Clock* pxWin32ClockReserve(PxMemoryArena* arena);

b32 pxWin32ClockCreate(PxWin32Clock* self);

f32 pxWin32ClockElapsed(PxWin32Clock* self);

#endif // PX_WIN32_TIME_CLOCK_H
