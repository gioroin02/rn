#ifndef RHO_SYSTEM_TIME_WIN32_CLOCK_C
#define RHO_SYSTEM_TIME_WIN32_CLOCK_C

#include "clock.h"

RWin32Clock* rho_win32_clock_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RWin32Clock, 1);
}

RBool32 rho_win32_clock_create(RWin32Clock* self)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->frequency.QuadPart = 0;
    self->counter.QuadPart   = 0;
    self->elapsed.QuadPart   = 0;

    BOOL status = QueryPerformanceFrequency(&self->frequency);

    if (status != 0) {
        status = QueryPerformanceCounter(&self->counter);

        if (status != 0) return 1;
    }

    return 0;
}

void rho_win32_clock_destroy(RWin32Clock* self)
{
    rho_memory_set(self, sizeof *self, 0xAB);
}

void rho_win32_clock_tick(RWin32Clock* self)
{
    LARGE_INTEGER counter = {0};

    BOOL status = QueryPerformanceCounter(&counter);

    if (status == 0) return;

    RUint time_next = counter.QuadPart;
    RUint time_curr = self->counter.QuadPart;

    if (time_next < time_curr) {
        RUint spare = RHO_UINT_MAX - time_curr;

        time_next += spare;
        time_curr  = 0;
    }

    self->elapsed.QuadPart =
        time_next - time_curr;

    self->counter = counter;
}

RUint rho_win32_clock_elapsed(RWin32Clock* self)
{
    return (RUint) self->elapsed.QuadPart;
}

RUint rho_win32_clock_frequency(RWin32Clock* self)
{
    return (RUint) self->frequency.QuadPart;
}

#endif
