#ifndef PX_SYSTEM_WINDOW_SURFACE_C
#define PX_SYSTEM_WINDOW_SURFACE_C

#include "surface.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../win32/window/export.c"

    #define __pxWindowSurfaceReserve__  pxWin32WindowSurfaceReserve
    #define __pxWindowSurfaceCreate__   pxWin32WindowSurfaceCreate
    #define __pxWindowSurfaceDestroy__  pxWin32WindowSurfaceDestroy
    #define __pxWindowSurfaceWidth__    pxWin32WindowSurfaceWidth
    #define __pxWindowSurfaceHeight__   pxWin32WindowSurfaceHeight
    #define __pxWindowSurfaceFill__     pxWin32WindowSurfaceFill
    #define __pxWindowSurfacePixelSet__ pxWin32WindowSurfacePixelSet
    #define __pxWindowSurfacePixelGet__ pxWin32WindowSurfacePixelGet

#else

    #error "Unknown platform"

#endif

PxWindowSurface* pxWindowSurfaceReserve(PxMemoryArena* arena)
{
    return __pxWindowSurfaceReserve__(arena);
}

b32 pxWindowSurfaceCreate(PxWindowSurface* self, PxMemoryArena* arena, ssize width, ssize height)
{
    return __pxWindowSurfaceCreate__(self, arena, width, height);
}

void pxWindowSurfaceDestroy(PxWindowSurface* self)
{
    return __pxWindowSurfaceDestroy__(self);
}

ssize pxWindowSurfaceWidth(PxWindowSurface* self)
{
    return __pxWindowSurfaceWidth__(self);
}

ssize pxWindowSurfaceHeight(PxWindowSurface* self)
{
    return __pxWindowSurfaceHeight__(self);
}

void pxWindowSurfaceFill(PxWindowSurface* self, u8 red, u8 green, u8 blue, u8 alpha)
{
    return __pxWindowSurfaceFill__(self, red, green, blue, alpha);
}

b32 pxWindowSurfacePixelSet(PxWindowSurface* self, ssize x, ssize y,
    u8 red, u8 green, u8 blue, u8 alpha)
{
    return __pxWindowSurfacePixelSet__(self, x, y, red, green, blue, alpha);
}

b32 pxWindowSurfacePixelGet(PxWindowSurface* self, ssize x, ssize y,
    u8* red, u8* green, u8* blue, u8* alpha)
{
    return __pxWindowSurfacePixelGet__(self, x, y, red, green, blue, alpha);
}

#endif // PX_SYSTEM_WINDOW_SURFACE_H
