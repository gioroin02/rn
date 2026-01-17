#ifndef P_SYSTEM_BITMAP_H
#define P_SYSTEM_BITMAP_H

#include "import.h"

typedef void PBitmap;

PBitmap* pBitmapReserve(PMemoryArena* arena);

b32 pBitmapCreate(PBitmap* self, PMemoryArena* arena, ssize width, ssize height);

ssize pBitmapWidth(PBitmap* self);

ssize pBitmapHeight(PBitmap* self);

void pBitmapFill(PBitmap* self, u8 red, u8 green, u8 blue, u8 alpha);

b32 pBitmapPixelSet(PBitmap* self, ssize x, ssize y, u8 red, u8 green, u8 blue, u8 alpha);

b32 pBitmapPixelGet(PBitmap* self, ssize x, ssize y, u8* red, u8* green, u8* blue, u8* alpha);

#endif // P_SYSTEM_BITMAP_H
