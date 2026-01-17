#ifndef P_SYSTEM_WIN32_BITMAP_C
#define P_SYSTEM_WIN32_BITMAP_C

#include "bitmap.h"

PWin32Bitmap* pWin32BitmapReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32Bitmap);
}

b32 pWin32BitmapCreate(PWin32Bitmap* self, PMemoryArena* arena, ssize width, ssize height)
{
    pMemorySet(self, sizeof* self, 0xAB);

    if (width <= 0 || height <= 0 || width > P_SSIZE_MAX / height) return 0;

    u32* pntr = pMemoryArenaReserveManyOf(arena, u32, width * height);

    if (pntr != NULL) {
        self->info.bmiHeader.biSize        = sizeof (BITMAPINFOHEADER);
        self->info.bmiHeader.biWidth       = width;
        self->info.bmiHeader.biHeight      = -height;
        self->info.bmiHeader.biPlanes      = 1;
        self->info.bmiHeader.biBitCount    = 32;
        self->info.bmiHeader.biCompression = BI_RGB;

        self->pntr   = pntr;
        self->width  = width;
        self->height = height;

        pWin32BitmapFill(self, 0, 0, 0, 0);

        return 1;
    }

    return 0;
}

ssize pWin32BitmapWidth(PWin32Bitmap* self)
{
    return self->width;
}

ssize pWin32BitmapHeight(PWin32Bitmap* self)
{
    return self->height;
}

void pWin32BitmapFill(PWin32Bitmap* self, u8 red, u8 green, u8 blue, u8 alpha)
{
    u32 color = ((u32) blue)  << 0
              | ((u32) green) << 8
              | ((u32) red)   << 16
              | ((u32) alpha) << 24;

    ssize row = 0;
    ssize col = 0;

    for (row = 0; row < self->height; row += 1) {
        for (col = 0; col < self->width; col += 1)
            self->pntr[self->width * row + col] = color;
    }
}

b32 pWin32BitmapPixelSet(PWin32Bitmap* self, ssize x, ssize y, u8 red, u8 green, u8 blue, u8 alpha)
{
    if (x < 0 || x >= self->width) return 0;
    if (y < 0 || y >= self->height) return 0;

    u32 color = ((u32) blue)  << 0
              | ((u32) green) << 8
              | ((u32) red)   << 16
              | ((u32) alpha) << 24;

    self->pntr[self->width * y + x] = color;

    return 1;
}

b32 pWin32BitmapPixelGet(PWin32Bitmap* self, ssize x, ssize y, u8* red, u8* green, u8* blue, u8* alpha)
{
    if (x < 0 || x >= self->width) return 0;
    if (y < 0 || y >= self->height) return 0;

    u32 color = self->pntr[self->width * y + x];

    if (red != NULL)   *blue  = (u8) ((color & 0x000000FF) >> 0);
    if (green != NULL) *green = (u8) ((color & 0x0000FF00) >> 8);
    if (blue != NULL)  *red   = (u8) ((color & 0x00FF0000) >> 16);
    if (alpha != NULL) *alpha = (u8) ((color & 0xFF000000) >> 24);

    return 1;
}

#endif // P_SYSTEM_WIN32_BITMAP_C
