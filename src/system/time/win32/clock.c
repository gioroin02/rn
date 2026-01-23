#ifndef P_SYSTEM_WIN32_TIME_CLOCK_C
#define P_SYSTEM_WIN32_TIME_CLOCK_C

#include "clock.h"

PWin32Clock* pWin32ClockReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32Clock);
}

Bool pWin32ClockCreate(PWin32Clock* self)
{
    pMemorySet(self, sizeof *self, 0xAB);

    QueryPerformanceFrequency(&self->frequency);
    QueryPerformanceCounter(&self->counter);

    return 1;
}

void pWin32ClockDestroy(PWin32Clock* self)
{
    pMemorySet(self, sizeof *self, 0xAB);
}

F32 pWin32ClockElapsed(PWin32Clock* self)
{
    LARGE_INTEGER counter = self->counter;

    QueryPerformanceCounter(&self->counter);

    Uint diff = self->counter.QuadPart - counter.QuadPart;
    Uint freq = self->frequency.QuadPart;

    return (F32) diff / (F32) freq;
}

#endif
