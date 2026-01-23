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

PWindow* pWindowReserve(PMemoryArena* arena)
{
    return (PWindow*) __pWindowReserve__(arena);
}

Bool pWindowCreate(PWindow* self, PString8 title, Int width, Int height)
{
    return __pWindowCreate__((__PWindow__*) self, title, width, height);
}

void pWindowDestroy(PWindow* self)
{
    return __pWindowDestroy__((__PWindow__*) self);
}

Bool pWindowPollEvent(PWindow* self, PWindowEvent* event)
{
    return __pWindowPollEvent__((__PWindow__*) self, event);
}

void pWindowSwapBuffers(PWindow* self)
{
    return __pWindowSwapBuffers__((__PWindow__*) self);
}

Bool pWindowSetAttribs(PWindow* self, PWindowAttribs attribs)
{
    return __pWindowSetAttribs__((__PWindow__*) self, attribs);
}

PWindowAttribs pWindowGetAttribs(PWindow* self)
{
    return __pWindowGetAttribs__((__PWindow__*) self);
}

Bool pWindowSetTimerCallback(PWindow* self, void* ctxt, void* proc)
{
    return __pWindowSetTimerCallback__((__PWindow__*) self, ctxt, proc);
}

void* pWindowGetTimerCallback(PWindow* self)
{
    return __pWindowGetTimerCallback__((__PWindow__*) self);
}

#endif // P_SYSTEM_WINDOW_WINDOW_C
