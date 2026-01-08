#ifndef PX_SYSTEM_WINDOW_WINDOW_C
#define PX_SYSTEM_WINDOW_WINDOW_C

#include "window.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../win32/window/export.c"

    #define __pxWindowReserve__       pxWin32WindowReserve
    #define __pxWindowCreate__        pxWin32WindowCreate
    #define __pxWindowDestroy__       pxWin32WindowDestroy
    #define __pxWindowVisibilitySet__ pxWin32WindowVisibilitySet

#else

    #error "Unknown platform"

#endif

PxWindow* pxWindowReserve(PxMemoryArena* arena)
{
    return __pxWindowReserve__(arena);
}

b32 pxWindowCreate(PxWindow* self, PxStr8 title, ssize width, ssize height)
{
    return __pxWindowCreate__(self, title, width, height);
}

void pxWindowDestroy(PxWindow* self)
{
    return __pxWindowDestroy__(self);
}

b32 pxWindowVisibilitySet(PxWindow* self, PxWindowVisibility visibility)
{
    return __pxWindowVisibilitySet__(self, visibility);
}

#endif // PX_SYSTEM_WINDOW_WINDOW_C
