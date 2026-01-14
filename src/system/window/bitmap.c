#ifndef PX_SYSTEM_BITMAP_C
#define PX_SYSTEM_BITMAP_C

#include "bitmap.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../win32/window/export.c"

    #define __pxBitmapReserve__  pxWin32BitmapReserve
    #define __pxBitmapCreate__   pxWin32BitmapCreate
    #define __pxBitmapWidth__    pxWin32BitmapWidth
    #define __pxBitmapHeight__   pxWin32BitmapHeight
    #define __pxBitmapFill__     pxWin32BitmapFill
    #define __pxBitmapPixelSet__ pxWin32BitmapPixelSet
    #define __pxBitmapPixelGet__ pxWin32BitmapPixelGet

#else

    #error "Unknown platform"

#endif

PxBitmap* pxBitmapReserve(PxMemoryArena* arena)
{
    return __pxBitmapReserve__(arena);
}

b32 pxBitmapCreate(PxBitmap* self, PxMemoryArena* arena, ssize width, ssize height)
{
    return __pxBitmapCreate__(self, arena, width, height);
}

ssize pxBitmapWidth(PxBitmap* self)
{
    return __pxBitmapWidth__(self);
}

ssize pxBitmapHeight(PxBitmap* self)
{
    return __pxBitmapHeight__(self);
}

void pxBitmapFill(PxBitmap* self, u8 red, u8 green, u8 blue, u8 alpha)
{
    return __pxBitmapFill__(self, red, green, blue, alpha);
}

b32 pxBitmapPixelSet(PxBitmap* self, ssize x, ssize y, u8 red, u8 green, u8 blue, u8 alpha)
{
    return __pxBitmapPixelSet__(self, x, y, red, green, blue, alpha);
}

b32 pxBitmapPixelGet(PxBitmap* self, ssize x, ssize y, u8* red, u8* green, u8* blue, u8* alpha)
{
    return __pxBitmapPixelGet__(self, x, y, red, green, blue, alpha);
}

#endif // PX_SYSTEM_BITMAP_H
