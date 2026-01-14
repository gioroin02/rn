#ifndef PX_SYSTEM_BITMAP_H
#define PX_SYSTEM_BITMAP_H

#include "import.h"

typedef void PxBitmap;

PxBitmap* pxBitmapReserve(PxMemoryArena* arena);

b32 pxBitmapCreate(PxBitmap* self, PxMemoryArena* arena, ssize width, ssize height);

ssize pxBitmapWidth(PxBitmap* self);

ssize pxBitmapHeight(PxBitmap* self);

void pxBitmapFill(PxBitmap* self, u8 red, u8 green, u8 blue, u8 alpha);

b32 pxBitmapPixelSet(PxBitmap* self, ssize x, ssize y, u8 red, u8 green, u8 blue, u8 alpha);

b32 pxBitmapPixelGet(PxBitmap* self, ssize x, ssize y, u8* red, u8* green, u8* blue, u8* alpha);

#endif // PX_SYSTEM_BITMAP_H
