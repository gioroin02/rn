#ifndef P_SYSTEM_WIN32_BITMAP_H
#define P_SYSTEM_WIN32_BITMAP_H

#include "common.h"

typedef struct PWin32Bitmap
{
    BITMAPINFO info;

    u32*  pntr;
    ssize width;
    ssize height;
}
PWin32Bitmap;

PWin32Bitmap* pWin32BitmapReserve(PMemoryArena* arena);

b32 pWin32BitmapCreate(PWin32Bitmap* self, PMemoryArena* arena, ssize width, ssize height);

ssize pWin32BitmapWidth(PWin32Bitmap* self);

ssize pWin32BitmapHeight(PWin32Bitmap* self);

void pWin32BitmapFill(PWin32Bitmap* self, u8 red, u8 green, u8 blue, u8 alpha);

b32 pWin32BitmapPixelSet(PWin32Bitmap* self, ssize x, ssize y, u8 red, u8 green, u8 blue, u8 alpha);

b32 pWin32BitmapPixelGet(PWin32Bitmap* self, ssize x, ssize y, u8* red, u8* green, u8* blue, u8* alpha);

#endif // P_SYSTEM_WIN32_BITMAP_H
