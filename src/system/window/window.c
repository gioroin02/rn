#ifndef P_SYSTEM_WINDOW_WINDOW_C
#define P_SYSTEM_WINDOW_WINDOW_C

#include "window.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PWindow__ PWin32Window

    #define __pWindowReserve__     pWin32WindowReserve
    #define __pWindowCreate__      pWin32WindowCreate
    #define __pWindowDestroy__     pWin32WindowDestroy
    #define __pWindowPollEvent__   pWin32WindowPollEvent
    #define __pWindowGetBuffer__   pWin32WindowGetBuffer
    #define __pWindowFlushBuffer__ pWin32WindowFlushBuffer

    #define __pWindowSetVisibility__  pWin32WindowSetVisibility
    #define __pWindowGetVisibility__  pWin32WindowGetVisibility

    #define __pWindowSetCallback__ pWin32WindowSetCallback
    #define __pWindowGetCallback__ pWin32WindowGetCallback

    /*
    #define __pWindowSetWidth__       pWin32WindowWidthSet
    #define __pWindowGetWidth__       pWin32WindowWidthGet
    #define __pWindowSetHeight__      pWin32WindowHeightSet
    #define __pWindowGetHeight__      pWin32WindowHeightGet
    */

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

PFrameBuffer* pWindowGetBuffer(PWindow* self)
{
    return (PFrameBuffer*) __pWindowGetBuffer__((__PWindow__*) self);
}

void pWindowFlushBuffer(PWindow* self)
{
    return __pWindowFlushBuffer__((__PWindow__*) self);
}

Bool pWindowSetVisibility(PWindow* self, PWindowVisibility visibility)
{
    return __pWindowSetVisibility__((__PWindow__*) self, visibility);
}

PWindowVisibility pWindowGetVisibility(PWindow* self)
{
    return __pWindowGetVisibility__((__PWindow__*) self);
}

Bool pWindowSetCallback(PWindow* self, void* ctxt, void* proc)
{
    return __pWindowSetCallback__((__PWindow__*) self, ctxt ,proc);
}

void* pWindowGetCallback(PWindow* self)
{
    return __pWindowGetCallback__((__PWindow__*) self);
}

/*
Int pWindowWidthSet(PWindow* self, Int width)
{
    return __pWindowWidthSet__((__PWindow__*) self, width);
}

Int pWindowWidthGet(PWindow* self)
{
    return __pWindowWidthGet__((__PWindow__*) self);
}

Int pWindowHeightSet(PWindow* self, Int height)
{
    return __pWindowHeightSet__((__PWindow__*) self, height);
}

Int pWindowHeightGet(PWindow* self)
{
    return __pWindowHeightGet__((__PWindow__*) self);
}
*/

#endif // P_SYSTEM_WINDOW_WINDOW_C
