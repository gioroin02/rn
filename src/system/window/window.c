#ifndef PX_SYSTEM_WINDOW_WINDOW_C
#define PX_SYSTEM_WINDOW_WINDOW_C

#include "window.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../win32/window/export.c"

    #define __pxWindowReserve__        pxWin32WindowReserve
    #define __pxWindowCreate__         pxWin32WindowCreate
    #define __pxWindowDestroy__        pxWin32WindowDestroy
    #define __pxWindowClear__          pxWin32WindowClear
    #define __pxWindowPaint__          pxWin32WindowPaint
    #define __pxWindowFlush__          pxWin32WindowFlush
    #define __pxWindowPollEvent__      pxWin32WindowPollEvent

    #define __pxWindowWidthSet__       pxWin32WindowWidthSet
    #define __pxWindowWidthGet__       pxWin32WindowWidthGet
    #define __pxWindowHeightSet__      pxWin32WindowHeightSet
    #define __pxWindowHeightGet__      pxWin32WindowHeightGet
    #define __pxWindowPntrContextSet__ pxWin32WindowPntrContextSet
    #define __pxWindowPntrContextGet__ pxWin32WindowPntrContextGet
    #define __pxWindowProcUpdateSet__  pxWin32WindowProcUpdateSet
    #define __pxWindowProcUpdateGet__  pxWin32WindowProcUpdateGet
    #define __pxWindowVisibilitySet__  pxWin32WindowVisibilitySet
    #define __pxWindowVisibilityGet__  pxWin32WindowVisibilityGet

#else

    #error "Unknown platform"

#endif

PxWindow* pxWindowReserve(PxMemoryArena* arena)
{
    return __pxWindowReserve__(arena);
}

b32 pxWindowCreate(PxWindow* self, PxString8 title, ssize width, ssize height, ssize scale)
{
    return __pxWindowCreate__(self, title, width, height, scale);
}

void pxWindowDestroy(PxWindow* self)
{
    return __pxWindowDestroy__(self);
}

void pxWindowClear(PxWindow* self, u8 red, u8 green, u8 blue)
{
    return __pxWindowClear__(self, red, green, blue);
}

void pxWindowPaint(PxWindow* self, ssize x, ssize y, ssize width, ssize height, PxBitmap* bitmap)
{
    return __pxWindowPaint__(self, x, y, width, height, bitmap);
}

void pxWindowFlush(PxWindow* self)
{
    return __pxWindowFlush__(self);
}

b32 pxWindowPollEvent(PxWindow* self, PxWindowEvent* event)
{
    return __pxWindowPollEvent__(self, event);
}

ssize pxWindowWidthSet(PxWindow* self, ssize width)
{
    return __pxWindowWidthSet__(self, width);
}

ssize pxWindowWidthGet(PxWindow* self)
{
    return __pxWindowWidthGet__(self);
}

ssize pxWindowHeightSet(PxWindow* self, ssize height)
{
    return __pxWindowHeightSet__(self, height);
}

ssize pxWindowHeightGet(PxWindow* self)
{
    return __pxWindowHeightGet__(self);
}

void* pxWindowPntrContextSet(PxWindow* self, void* ctxt)
{
    return __pxWindowPntrContextSet__(self, ctxt);
}

void* pxWindowPntrContextGet(PxWindow* self)
{
    return __pxWindowPntrContextGet__(self);
}

void* pxWindowProcUpdateSet(PxWindow* self, void* proc)
{
    return __pxWindowProcUpdateSet__(self, proc);
}

void* pxWindowProcUpdateGet(PxWindow* self)
{
    return __pxWindowProcUpdateGet__(self);
}

b32 pxWindowVisibilitySet(PxWindow* self, PxWindowVisibility visibility)
{
    return __pxWindowVisibilitySet__(self, visibility);
}

PxWindowVisibility pxWindowVisibilityGet(PxWindow* self)
{
    return __pxWindowVisibilityGet__(self);
}

#endif // PX_SYSTEM_WINDOW_WINDOW_C
