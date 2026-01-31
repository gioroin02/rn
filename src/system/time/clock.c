#ifndef RHO_SYSTEM_TIME_CLOCK_C
#define RHO_SYSTEM_TIME_CLOCK_C

#include "clock.h"

#if RHO_SYSTEM == RHO_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __RClock__ RWin32Clock

    #define __rho_clock_reserve__   rho_win32_clock_reserve
    #define __rho_clock_create__    rho_win32_clock_create
    #define __rho_clock_destroy__   rho_win32_clock_destroy
    #define __rho_clock_tick__      rho_win32_clock_tick
    #define __rho_clock_elapsed__   rho_win32_clock_elapsed
    #define __rho_clock_frequency__ rho_win32_clock_frequency

#elif RHO_SYSTEM == RHO_SYSTEM_LINUX

    #include "linux/export.c"

    #define __RClock__ RLinuxClock

    #define __rho_clock_reserve__   rho_linux_clock_reserve
    #define __rho_clock_create__    rho_linux_clock_create
    #define __rho_clock_destroy__   rho_linux_clock_destroy
    #define __rho_clock_tick__      rho_linux_clock_tick
    #define __rho_clock_elapsed__   rho_linux_clock_elapsed
    #define __rho_clock_frequency__ rho_linux_clock_frequency

#else

    #error "Unknown platform"

#endif

RClock* rho_clock_reserve(RMemoryArena* arena)
{
    return (RClock*) __rho_clock_reserve__(arena);
}

RBool32 rho_clock_create(RClock* self)
{
    return __rho_clock_create__((__RClock__*) self);
}

void rho_clock_destroy(RClock* self)
{
    return __rho_clock_destroy__((__RClock__*) self);
}

void rho_clock_tick(RClock* self)
{
    return __rho_clock_tick__((__RClock__*) self);
}

RUint rho_clock_elapsed(RClock* self)
{
    return __rho_clock_elapsed__((__RClock__*) self);
}

RUint rho_clock_frequency(RClock* self)
{
    return __rho_clock_frequency__((__RClock__*) self);
}

RFloat32 rho_clock_seconds(RClock* self)
{
    RFloat32 elapsed   = (RFloat32) rho_clock_elapsed(self);
    RFloat32 frequency = (RFloat32) rho_clock_frequency(self);

    return elapsed / frequency;
}

#endif
