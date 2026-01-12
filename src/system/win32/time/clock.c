#ifndef PX_WIN32_TIME_CLOCK_C
#define PX_WIN32_TIME_CLOCK_C

#include "clock.h"

PxWin32Clock* pxWin32ClockReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32Clock);
}

b32 pxWin32ClockCreate(PxWin32Clock* self)
{
    QueryPerformanceFrequency(&self->frequency);

    QueryPerformanceCounter(&self->tick_previous);
    QueryPerformanceCounter(&self->tick_current);

    return 1;
}

f32 pxWin32ClockElapsed(PxWin32Clock* self)
{
    self->tick_previous = self->tick_current;

    QueryPerformanceCounter(&self->tick_current);

    usize delta = self->tick_current.QuadPart -
        self->tick_previous.QuadPart;

    usize freq = self->frequency.QuadPart;

    return (f32) (delta) / (f32) (freq);
}

#endif // PX_WIN32_TIME_CLOCK_C
