#ifndef PX_WIN32_WINDOW_SURFACE_H
#define PX_WIN32_WINDOW_SURFACE_H

#include "common.h"

typedef struct PxWin32WindowSurface
{
    HBITMAP    handle;
    BITMAPINFO info;
    u32*       pntr;
    ssize      width;
    ssize      height;
}
PxWin32WindowSurface;

PxWin32WindowSurface* pxWin32WindowSurfaceReserve(PxMemoryArena* arena);

b32 pxWin32WindowSurfaceCreate(PxWin32WindowSurface* self, PxMemoryArena* arena, ssize width, ssize height);

void pxWin32WindowSurfaceDestroy(PxWin32WindowSurface* self);

ssize pxWin32WindowSurfaceWidth(PxWin32WindowSurface* self);

ssize pwWin32WindowSurfaceHeight(PxWin32WindowSurface* self);

void pxWin32WindowSurfaceFill(PxWin32WindowSurface* self, u8 red, u8 green, u8 blue, u8 alpha);

b32 pxWin32WindowSurfacePixelSet(PxWin32WindowSurface* self, ssize x, ssize y,
    u8 red, u8 green, u8 blue, u8 alpha);

b32 pxWin32WindowSurfacePixelGet(PxWin32WindowSurface* self, ssize x, ssize y,
    u8* red, u8* green, u8* blue, u8* alpha);

#endif // PX_WIN32_WINDOW_SURFACE_H
