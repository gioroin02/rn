#ifndef P_SYSTEM_WINDOW_WINDOW_C
#define P_SYSTEM_WINDOW_WINDOW_C

#include "window.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PWindow__ PWin32Window

    #define __pWindowReserve__          pWin32WindowReserve
    #define __pWindowCreate__           pWin32WindowCreate
    #define __pWindowDestroy__          pWin32WindowDestroy
    #define __pWindowPollEvent__        pWin32WindowPollEvent
    #define __pWindowSwapBuffers__      pWin32WindowSwapBuffers
    #define __pWindowSetAttribs__       pWin32WindowSetAttribs
    #define __pWindowGetAttribs__       pWin32WindowGetAttribs
    #define __pWindowSetTimerCallback__ pWin32WindowSetTimerCallback
    #define __pWindowGetTimerCallback__ pWin32WindowGetTimerCallback

#else

    #error "Unknown platform"

#endif

PWindowAttribs pWindowAttribsMake()
{
    PWindowAttribs result = {0};

    pMemorySet(&result, sizeof result, 0xAB);

    result.visibility = PWindowVisibility_None;
    result.coord_x    = 0;
    result.coord_y    = 0;
    result.width      = 0;
    result.width_max  = 0;
    result.width_min  = 0;
    result.height     = 0;
    result.height_max = 0;
    result.height_min = 0;

    return result;
}

PWindow* pWindowReserve(PMemoryArena* arena)
{
    return (PWindow*) __pWindowReserve__(arena);
}

B32 pWindowCreate(PWindow* self, PString8 title, Int width, Int height)
{
    return __pWindowCreate__((__PWindow__*) self, title, width, height);
}

void pWindowDestroy(PWindow* self)
{
    return __pWindowDestroy__((__PWindow__*) self);
}

B32 pWindowPollEvent(PWindow* self, PWindowEvent* event)
{
    return __pWindowPollEvent__((__PWindow__*) self, event);
}

void pWindowSwapBuffers(PWindow* self)
{
    return __pWindowSwapBuffers__((__PWindow__*) self);
}

B32 pWindowSetAttribs(PWindow* self, PWindowAttribs attribs)
{
    return __pWindowSetAttribs__((__PWindow__*) self, attribs);
}

PWindowAttribs pWindowGetAttribs(PWindow* self)
{
    return __pWindowGetAttribs__((__PWindow__*) self);
}

B32 pWindowSetTimerCallback(PWindow* self, void* ctxt, void* proc)
{
    return __pWindowSetTimerCallback__((__PWindow__*) self, ctxt, proc);
}

void* pWindowGetTimerCallback(PWindow* self)
{
    return __pWindowGetTimerCallback__((__PWindow__*) self);
}

#endif
