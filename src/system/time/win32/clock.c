#ifndef P_SYSTEM_WIN32_TIME_CLOCK_C
#define P_SYSTEM_WIN32_TIME_CLOCK_C

#include "clock.h"

PWin32Clock* pWin32ClockReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32Clock);
}

B32 pWin32ClockCreate(PWin32Clock* self)
{
    pMemorySet(self, sizeof *self, 0xAB);

    BOOL status = QueryPerformanceFrequency(&self->frequency);

    if (status != 0) {
        status = QueryPerformanceCounter(&self->counter);

        if (status != 0)
            return 1;
    }

    self->counter.QuadPart   = 0;
    self->frequency.QuadPart = 0;

    return 0;
}

void pWin32ClockDestroy(PWin32Clock* self)
{
    pMemorySet(self, sizeof *self, 0xAB);
}

F32 pWin32ClockElapsed(PWin32Clock* self)
{
    LARGE_INTEGER counter = {0};

    BOOL status = QueryPerformanceCounter(&counter);

    if (status == 0) return P_F32_NAN;

    Uint diff = counter.QuadPart - self->counter.QuadPart;
    Uint freq = self->frequency.QuadPart;

    self->counter = counter;

    return (F32) diff / (F32) freq;
}

#endif
