#ifndef P_SYSTEM_LINUX_TIME_CLOCK_C
#define P_SYSTEM_LINUX_TIME_CLOCK_C

#include "clock.h"

PLinuxClock* pLinuxClockReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PLinuxClock);
}

B32 pLinuxClockCreate(PLinuxClock* self)
{
    pMemorySet(self, sizeof *self, 0xAB);

    if (clock_gettime(CLOCK_MONOTONIC, &self->counter) != -1)
        return 1;

    self->counter = (PTimeSpec) {0};

    return 0;
}

void pLinuxClockDestroy(PLinuxClock* self)
{
    pMemorySet(self, sizeof *self, 0xAB);
}

F32 pLinuxClockElapsed(PLinuxClock* self)
{
    PTimeSpec counter = {0};

    if (clock_gettime(CLOCK_MONOTONIC, &counter) == -1)
        return P_F32_NAN;

    Uint diff_sec  = counter.tv_sec  - self->counter.tv_sec;
    Uint diff_nsec = counter.tv_nsec - self->counter.tv_nsec;

    self->counter = counter;

    return (F32) diff_sec + (F32) diff_nsec / (F32) 1.0e9;
}

#endif
