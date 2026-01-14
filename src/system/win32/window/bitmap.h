#ifndef PX_WIN32_BITMAP_H
#define PX_WIN32_BITMAP_H

#include "common.h"

typedef struct PxWin32Bitmap
{
    BITMAPINFO info;

    u32*  pntr;
    ssize width;
    ssize height;
}
PxWin32Bitmap;

PxWin32Bitmap* pxWin32BitmapReserve(PxMemoryArena* arena);

b32 pxWin32BitmapCreate(PxWin32Bitmap* self, PxMemoryArena* arena, ssize width, ssize height);

ssize pxWin32BitmapWidth(PxWin32Bitmap* self);

ssize pxWin32BitmapHeight(PxWin32Bitmap* self);

void pxWin32BitmapFill(PxWin32Bitmap* self, u8 red, u8 green, u8 blue, u8 alpha);

b32 pxWin32BitmapPixelSet(PxWin32Bitmap* self, ssize x, ssize y, u8 red, u8 green, u8 blue, u8 alpha);

b32 pxWin32BitmapPixelGet(PxWin32Bitmap* self, ssize x, ssize y, u8* red, u8* green, u8* blue, u8* alpha);

#endif // PX_WIN32_BITMAP_H
