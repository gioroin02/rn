#ifndef PX_SYSTEM_WINDOW_WINDOW_C
#define PX_SYSTEM_WINDOW_WINDOW_C

#include "window.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../win32/window/export.c"

    #define __pxWindowReserve__       pxWin32WindowReserve
    #define __pxWindowCreate__        pxWin32WindowCreate
    #define __pxWindowDestroy__       pxWin32WindowDestroy
    #define __pxWindowWidth__         pxWin32WindowWidth
    #define __pxWindowHeight__        pxWin32WindowHeight
    #define __pxWindowClear__         pxWin32WindowClear
    #define __pxWindowPaint__         pxWin32WindowPaint
    #define __pxWindowFlush__         pxWin32WindowFlush
    #define __pxWindowPollEvent__     pxWin32WindowPollEvent
    #define __pxWindowVisibilitySet__ pxWin32WindowVisibilitySet
    #define __pxWindowProcPaintSet__  pxWin32WindowProcPaintSet

#else

    #error "Unknown platform"

#endif

PxWindow* pxWindowReserve(PxMemoryArena* arena)
{
    return __pxWindowReserve__(arena);
}

b32 pxWindowCreate(PxWindow* self, PxString8 title, ssize width, ssize height)
{
    return __pxWindowCreate__(self, title, width, height);
}

void pxWindowDestroy(PxWindow* self)
{
    return __pxWindowDestroy__(self);
}

ssize pxWindowWidth(PxWindow* self)
{
    return __pxWindowWidth__(self);
}

ssize pxWindowHeight(PxWindow* self)
{
    return __pxWindowHeight__(self);
}

void pxWindowClear(PxWindow* self, u8 red, u8 green, u8 blue)
{
    return __pxWindowClear__(self, red, green, blue);
}

void pxWindowPaint(PxWindow* self, ssize x, ssize y, ssize width, ssize height, PxWindowSurface* surface)
{
    return __pxWindowPaint__(self, x, y, width, height, surface);
}

void pxWindowFlush(PxWindow* self)
{
    return __pxWindowFlush__(self);
}

b32 pxWindowPollEvent(PxWindow* self, PxWindowEvent* event)
{
    return __pxWindowPollEvent__(self, event);
}

b32 pxWindowVisibilitySet(PxWindow* self, PxWindowVisibility visibility)
{
    return __pxWindowVisibilitySet__(self, visibility);
}

void pxWindowProcPaintSet(PxWindow* self, void* ctxt, void* proc)
{
    return __pxWindowProcPaintSet__(self, ctxt, proc);
}

#endif // PX_SYSTEM_WINDOW_WINDOW_C
