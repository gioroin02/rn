#ifndef PX_SYSTEM_WINDOW_WINDOW_C
#define PX_SYSTEM_WINDOW_WINDOW_C

#include "window.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../win32/window/export.c"

    #define __pxWindowReserve__       pxWin32WindowReserve
    #define __pxWindowCreate__        pxWin32WindowCreate
    #define __pxWindowDestroy__       pxWin32WindowDestroy
    #define __pxWindowClear__         pxWin32WindowClear
    #define __pxWindowFlush__         pxWin32WindowFlush
    #define __pxWindowPollEvent__     pxWin32WindowPollEvent
    #define __pxWindowVisibilitySet__ pxWin32WindowVisibilitySet
    #define __pxWindowClearColorSet__ pxWin32WindowClearColorSet

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

void pxWindowClear(PxWindow* self)
{
    return __pxWindowClear__(self);
}

void pxWindowFlush(PxWindow* self, PxWindowSurface* surface)
{
    return __pxWindowFlush__(self, surface);
}

b32 pxWindowPollEvent(PxWindow* self, PxWindowEvent* event)
{
    return __pxWindowPollEvent__(self, event);
}

b32 pxWindowVisibilitySet(PxWindow* self, PxWindowVisibility visibility)
{
    return __pxWindowVisibilitySet__(self, visibility);
}

void pxWindowClearColorSet(PxWindow* self, u8 red, u8 green, u8 blue, u8 alpha)
{
    return __pxWindowClearColorSet__(self, red, green, blue, alpha);
}

#endif // PX_SYSTEM_WINDOW_WINDOW_C
