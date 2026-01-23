#ifndef P_SYSTEM_LINUX_TIME_CLOCK_C
#define P_SYSTEM_LINUX_TIME_CLOCK_C

#include "clock.h"

PLinuxClock* pLinuxClockReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PLinuxClock);
}

Bool pLinuxClockCreate(PLinuxClock* self)
{
    pMemorySet(self, sizeof *self, 0xAB);

    if (clock_gettime(CLOCK_MONOTONIC, &self->counter) < 0)
        return 0;

    return 1;
}

void pLinuxClockDestroy(PLinuxClock* self)
{
    pMemorySet(self, sizeof *self, 0xAB);
}

F32 pLinuxClockElapsed(PLinuxClock* self)
{
    PTimeSpec counter = self->counter;

    clock_gettime(CLOCK_MONOTONIC, &self->counter);

    Uint diff_sec  = self->counter.tv_sec  - counter.tv_sec;
    Uint diff_nsec = self->counter.tv_nsec - counter.tv_nsec;

    return (F32) diff_sec + (F32) diff_nsec / (F32) 1.0e9;
}

#endif
