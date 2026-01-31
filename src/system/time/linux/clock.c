#ifndef RHO_SYSTEM_TIME_LINUX_CLOCK_C
#define RHO_SYSTEM_TIME_LINUX_CLOCK_C

#include "clock.h"

#define RHO_LINUX_CLOCK_FREQUENCY ((RUint) 1000000000llu)

RLinuxClock* rho_linux_clock_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RLinuxClock, 1);
}

RBool32 rho_linux_clock_create(RLinuxClock* self)
{
    rho_memory_set(self, sizeof *self, 0xAB);

    self->counter = (RLinuxTimeSpec) {0};
    self->elapsed = (RLinuxTimeSpec) {0};

    if (clock_gettime(CLOCK_MONOTONIC, &self->counter) != -1)
        return 1;

    return 0;
}

void rho_linux_clock_destroy(RLinuxClock* self)
{
    rho_memory_set(self, sizeof *self, 0xAB);
}

void rho_linux_clock_tick(RLinuxClock* self)
{
    RLinuxTimeSpec counter = {0};

    if (clock_gettime(CLOCK_MONOTONIC, &counter) == -1) return;

    RUint sec_next  = counter.tv_sec;
    RUint sec_curr  = self->counter.tv_sec;
    RUint nsec_next = counter.tv_nsec;
    RUint nsec_curr = self->counter.tv_nsec;

    RUint time_next = sec_next + nsec_next * RHO_LINUX_CLOCK_FREQUENCY;
    RUint time_curr = sec_curr + nsec_curr * RHO_LINUX_CLOCK_FREQUENCY;

    if (time_next < time_curr) {
        RUint spare = RHO_UINT_MAX - time_curr;

        sec_next  += spare / RHO_LINUX_CLOCK_FREQUENCY;
        sec_curr   = 0;
        nsec_next += spare % RHO_LINUX_CLOCK_FREQUENCY;
        nsec_curr  = 0;
    }

    self->elapsed.tv_sec  = sec_next;
    self->elapsed.tv_nsec = nsec_next;

    self->counter = counter;
}

RUint rho_linux_clock_elapsed(RLinuxClock* self)
{
    return self->elapsed.tv_sec +
        self->elapsed.tv_nsec * RHO_LINUX_CLOCK_FREQUENCY;
}

RUint rho_linux_clock_frequency(RLinuxClock* self)
{
    return RHO_LINUX_CLOCK_FREQUENCY;
}

#endif
