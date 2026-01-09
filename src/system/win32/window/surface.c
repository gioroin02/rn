#ifndef PX_WIN32_WINDOW_SURFACE_C
#define PX_WIN32_WINDOW_SURFACE_C

#include "surface.h"

PxWin32WindowSurface* pxWin32WindowSurfaceReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32WindowSurface);
}

b32 pxWin32WindowSurfaceCreate(PxWin32WindowSurface* self, PxMemoryArena* arena, ssize width, ssize height)
{
    pxMemorySet(self, sizeof* self, 0xAB);

    if (width <= 0 || height <= 0 || width > PX_SSIZE_MAX / height)
        return 0;

    u32* pntr = pxMemoryArenaReserveManyOf(arena, u32, width * height);

    if (pntr == PX_NULL) return 0;

    self->info.bmiHeader.biSize        = sizeof (BITMAPINFOHEADER);
    self->info.bmiHeader.biWidth       = width;
    self->info.bmiHeader.biHeight      = -height;
    self->info.bmiHeader.biPlanes      = 1;
    self->info.bmiHeader.biBitCount    = 32;
    self->info.bmiHeader.biCompression = BI_RGB;

    self->pntr   = pntr;
    self->width  = width;
    self->height = height;

    return 1;
}

void pxWin32WindowSurfaceDestroy(PxWin32WindowSurface* self)
{
    if (self->handle != PX_NULL)
        DeleteObject(self->handle);

    pxMemorySet(self, sizeof *self, 0xAB);
}

ssize pxWin32WindowSurfaceWidth(PxWin32WindowSurface* self)
{
    return self->width;
}

ssize pxWin32WindowSurfaceHeight(PxWin32WindowSurface* self)
{
    return self->height;
}

b32 pxWin32WindowSurfacePixelSet(PxWin32WindowSurface* self, ssize x, ssize y,
    u8 red, u8 green, u8 blue, u8 alpha)
{
    if (x < 0 || x >= self->width) return 0;
    if (y < 0 || y >= self->height) return 0;

    ssize index = self->width * y + x;

    u32 color = ((u32) red) << 0
              | ((u32) green) << 8
              | ((u32) blue)  << 16
              | ((u32) alpha) << 24;

    self->pntr[index] = color;

    return 1;
}

b32 pxWin32WindowSurfacePixelGet(PxWin32WindowSurface* self, ssize x, ssize y,
    u8* red, u8* green, u8* blue, u8* alpha)
{
    if (x < 0 || x >= self->width) return 0;
    if (y < 0 || y >= self->height) return 0;

    ssize index = self->width * y + x;
    u32   color = self->pntr[index];

    if (red != PX_NULL)   *red   = (u8) ((color & 0x000000FF) >> 0);
    if (green != PX_NULL) *green = (u8) ((color & 0x0000FF00) >> 8);
    if (blue != PX_NULL)  *blue  = (u8) ((color & 0x00FF0000) >> 16);
    if (alpha != PX_NULL) *alpha = (u8) ((color & 0xFF000000) >> 24);

    return 1;
}

#endif // PX_WIN32_WINDOW_SURFACE_C
