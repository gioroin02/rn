#ifndef P_SYSTEM_BITMAP_C
#define P_SYSTEM_BITMAP_C

#include "bitmap.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "../win32/window/export.c"

    #define __pBitmapReserve__  pWin32BitmapReserve
    #define __pBitmapCreate__   pWin32BitmapCreate
    #define __pBitmapWidth__    pWin32BitmapWidth
    #define __pBitmapHeight__   pWin32BitmapHeight
    #define __pBitmapFill__     pWin32BitmapFill
    #define __pBitmapPixelSet__ pWin32BitmapPixelSet
    #define __pBitmapPixelGet__ pWin32BitmapPixelGet

#else

    #error "Unknown platform"

#endif

PBitmap* pBitmapReserve(PMemoryArena* arena)
{
    return __pBitmapReserve__(arena);
}

b32 pBitmapCreate(PBitmap* self, PMemoryArena* arena, ssize width, ssize height)
{
    return __pBitmapCreate__(self, arena, width, height);
}

ssize pBitmapWidth(PBitmap* self)
{
    return __pBitmapWidth__(self);
}

ssize pBitmapHeight(PBitmap* self)
{
    return __pBitmapHeight__(self);
}

void pBitmapFill(PBitmap* self, u8 red, u8 green, u8 blue, u8 alpha)
{
    return __pBitmapFill__(self, red, green, blue, alpha);
}

b32 pBitmapPixelSet(PBitmap* self, ssize x, ssize y, u8 red, u8 green, u8 blue, u8 alpha)
{
    return __pBitmapPixelSet__(self, x, y, red, green, blue, alpha);
}

b32 pBitmapPixelGet(PBitmap* self, ssize x, ssize y, u8* red, u8* green, u8* blue, u8* alpha)
{
    return __pBitmapPixelGet__(self, x, y, red, green, blue, alpha);
}

#endif // P_SYSTEM_BITMAP_H
