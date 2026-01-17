#ifndef P_SYSTEM_WINDOW_WINDOW_C
#define P_SYSTEM_WINDOW_WINDOW_C

#include "window.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "../win32/window/export.c"

    #define __pWindowReserve__        pWin32WindowReserve
    #define __pWindowCreate__         pWin32WindowCreate
    #define __pWindowDestroy__        pWin32WindowDestroy
    #define __pWindowClear__          pWin32WindowClear
    #define __pWindowPaint__          pWin32WindowPaint
    #define __pWindowFlush__          pWin32WindowFlush
    #define __pWindowPollEvent__      pWin32WindowPollEvent

    #define __pWindowWidthSet__       pWin32WindowWidthSet
    #define __pWindowWidthGet__       pWin32WindowWidthGet
    #define __pWindowHeightSet__      pWin32WindowHeightSet
    #define __pWindowHeightGet__      pWin32WindowHeightGet
    #define __pWindowPntrContextSet__ pWin32WindowPntrContextSet
    #define __pWindowPntrContextGet__ pWin32WindowPntrContextGet
    #define __pWindowProcUpdateSet__  pWin32WindowProcUpdateSet
    #define __pWindowProcUpdateGet__  pWin32WindowProcUpdateGet
    #define __pWindowVisibilitySet__  pWin32WindowVisibilitySet
    #define __pWindowVisibilityGet__  pWin32WindowVisibilityGet

#else

    #error "Unknown platform"

#endif

PWindow* pWindowReserve(PMemoryArena* arena)
{
    return __pWindowReserve__(arena);
}

b32 pWindowCreate(PWindow* self, PString8 title, ssize width, ssize height)
{
    return __pWindowCreate__(self, title, width, height);
}

void pWindowDestroy(PWindow* self)
{
    return __pWindowDestroy__(self);
}

void pWindowClear(PWindow* self, u8 red, u8 green, u8 blue)
{
    return __pWindowClear__(self, red, green, blue);
}

void pWindowPaint(PWindow* self, ssize x, ssize y, ssize width, ssize height, PBitmap* bitmap)
{
    return __pWindowPaint__(self, x, y, width, height, bitmap);
}

void pWindowFlush(PWindow* self)
{
    return __pWindowFlush__(self);
}

b32 pWindowPollEvent(PWindow* self, PWindowEvent* event)
{
    return __pWindowPollEvent__(self, event);
}

ssize pWindowWidthSet(PWindow* self, ssize width)
{
    return __pWindowWidthSet__(self, width);
}

ssize pWindowWidthGet(PWindow* self)
{
    return __pWindowWidthGet__(self);
}

ssize pWindowHeightSet(PWindow* self, ssize height)
{
    return __pWindowHeightSet__(self, height);
}

ssize pWindowHeightGet(PWindow* self)
{
    return __pWindowHeightGet__(self);
}

void* pWindowPntrContextSet(PWindow* self, void* ctxt)
{
    return __pWindowPntrContextSet__(self, ctxt);
}

void* pWindowPntrContextGet(PWindow* self)
{
    return __pWindowPntrContextGet__(self);
}

void* pWindowProcUpdateSet(PWindow* self, void* proc)
{
    return __pWindowProcUpdateSet__(self, proc);
}

void* pWindowProcUpdateGet(PWindow* self)
{
    return __pWindowProcUpdateGet__(self);
}

b32 pWindowVisibilitySet(PWindow* self, PWindowVisibility visibility)
{
    return __pWindowVisibilitySet__(self, visibility);
}

PWindowVisibility pWindowVisibilityGet(PWindow* self)
{
    return __pWindowVisibilityGet__(self);
}

#endif // P_SYSTEM_WINDOW_WINDOW_C
