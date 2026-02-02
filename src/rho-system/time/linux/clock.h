#ifndef RHO_SYSTEM_TIME_LINUX_CLOCK_H
#define RHO_SYSTEM_TIME_LINUX_CLOCK_H

#include "import.h"

#ifndef _DEFAULT_SOURCE

    #define _DEFAULT_SOURCE

#endif

#include <unistd.h>
#include <time.h>

typedef struct timespec RLinuxTimeSpec;

typedef struct RLinuxClock
{
    RLinuxTimeSpec counter;
    RLinuxTimeSpec elapsed;
}
RLinuxClock;

RLinuxClock* rho_linux_clock_reserve(RMemoryArena* arena);

RBool32 rho_linux_clock_create(RLinuxClock* self);

void rho_linux_clock_destroy(RLinuxClock* self);

void rho_linux_clock_tick(RLinuxClock* self);

RUint rho_linux_clock_elapsed(RLinuxClock* self);

RUint rho_linux_clock_frequency(RLinuxClock* self);

#endif
