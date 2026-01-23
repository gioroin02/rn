#ifndef P_SYSTEM_TIME_CLOCK_C
#define P_SYSTEM_TIME_CLOCK_C

#include "clock.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PClock__ PWin32Clock

    #define __pClockReserve__ pWin32ClockReserve
    #define __pClockCreate__  pWin32ClockCreate
    #define __pClockDestroy__ pWin32ClockDestroy
    #define __pClockElapsed__ pWin32ClockElapsed

#elif P_SYSTEM == P_SYSTEM_LINUX

    #include "linux/export.c"

    #define __PClock__ PLinuxClock

    #define __pClockReserve__ pLinuxClockReserve
    #define __pClockCreate__  pLinuxClockCreate
    #define __pClockDestroy__ pLinuxClockDestroy
    #define __pClockElapsed__ pLinuxClockElapsed

#else

    #error "Unknown platform"

#endif

PClock* pClockReserve(PMemoryArena* arena)
{
    return (PClock*) __pClockReserve__(arena);
}

Bool pClockCreate(PClock* self)
{
    return __pClockCreate__((__PClock__*) self);
}

void pClockDestroy(PClock* self)
{
    return __pClockDestroy__((__PClock__*) self);
}

F32 pClockElapsed(PClock* self)
{
    return __pClockElapsed__((__PClock__*) self);
}

#endif
