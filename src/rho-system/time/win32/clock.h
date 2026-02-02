#ifndef RHO_SYSTEM_TIME_WIN32_CLOCK_H
#define RHO_SYSTEM_TIME_WIN32_CLOCK_H

#include "import.h"

#define WIN32_LEAN_AND_MEAN
#define NOGDI

#include <windows.h>

typedef struct RWin32Clock
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER counter;
    LARGE_INTEGER elapsed;
}
RWin32Clock;

RWin32Clock* rho_win32_clock_reserve(RMemoryArena* arena);

RBool32 rho_win32_clock_create(RWin32Clock* self);

void rho_win32_clock_destroy(RWin32Clock* self);

void rho_win32_clock_tick(RWin32Clock* self);

RUint rho_win32_clock_elapsed(RWin32Clock* self);

RUint rho_win32_clock_frequency(RWin32Clock* self);

#endif
