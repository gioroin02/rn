#ifndef PX_SYSTEM_WINDOW_SURFACE_H
#define PX_SYSTEM_WINDOW_SURFACE_H

#include "import.h"

typedef void PxWindowSurface;

PxWindowSurface* pxWindowSurfaceReserve(PxMemoryArena* arena);

b32 pxWindowSurfaceCreate(PxWindowSurface* self, PxMemoryArena* arena, ssize width, ssize height);

void pxWindowSurfaceDestroy(PxWindowSurface* self);

ssize pxWindowSurfaceWidth(PxWindowSurface* self);

ssize pxWindowSurfaceHeight(PxWindowSurface* self);

b32 pxWindowSurfacePixelSet(PxWindowSurface* self, ssize x, ssize y,
    u8 red, u8 green, u8 blue, u8 alpha);

b32 pxWindowSurfacePixelGet(PxWindowSurface* self, ssize x, ssize y,
    u8* red, u8* green, u8* blue, u8* alpha);

#endif // PX_SYSTEM_WINDOW_SURFACE_H
