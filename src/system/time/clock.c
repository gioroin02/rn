#ifndef PX_SYSTEM_TIME_CLOCK_C
#define PX_SYSTEM_TIME_CLOCK_C

#include "clock.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../win32/time/export.c"

    #define __pxClockReserve__ pxWin32ClockReserve
    #define __pxClockCreate__  pxWin32ClockCreate
    #define __pxClockElapsed__ pxWin32ClockElapsed

#else

    #error "Unknown platform"

#endif

PxClock* pxClockReserve(PxMemoryArena* arena)
{
    return __pxClockReserve__(arena);
}

b32 pxClockCreate(PxClock* self)
{
    return __pxClockCreate__(self);
}

f32 pxClockElapsed(PxClock* self)
{
    return __pxClockElapsed__(self);
}

#endif // PX_SYSTEM_TIME_CLOCK_C
