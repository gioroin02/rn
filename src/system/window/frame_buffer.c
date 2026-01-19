#ifndef P_SYSTEM_FRAME_BUFFER_C
#define P_SYSTEM_FRAME_BUFFER_C

#include "frame_buffer.h"

#if P_SYSTEM == P_SYSTEM_WINDOWS

    #include "win32/export.c"

    #define __PFrameBuffer__ PWin32FrameBuffer

    #define __pFrameBufferReserve__ pWin32FrameBufferReserve
    #define __pFrameBufferCreate__  pWin32FrameBufferCreate
    #define __pFrameBufferWidth__   pWin32FrameBufferWidth
    #define __pFrameBufferHeight__  pWin32FrameBufferHeight
    #define __pFrameBufferFill__    pWin32FrameBufferFill
    #define __pFrameBufferSet__     pWin32FrameBufferSet
    #define __pFrameBufferBlend__   pWin32FrameBufferBlend
    #define __pFrameBufferGet__     pWin32FrameBufferGet

#else

    #error "Unknown platform"

#endif

PFrameBuffer* pFrameBufferReserve(PMemoryArena* arena)
{
    return (PFrameBuffer*) __pFrameBufferReserve__(arena);
}

Bool pFrameBufferCreate(PFrameBuffer* self, Int width, Int height)
{
    return __pFrameBufferCreate__((__PFrameBuffer__*) self, width, height);
}

Int pFrameBufferWidth(PFrameBuffer* self)
{
    return __pFrameBufferWidth__((__PFrameBuffer__*) self);
}

Int pFrameBufferHeight(PFrameBuffer* self)
{
    return __pFrameBufferHeight__((__PFrameBuffer__*) self);
}

void pFrameBufferFill(PFrameBuffer* self, U8 red, U8 green, U8 blue, U8 alpha)
{
    return __pFrameBufferFill__((__PFrameBuffer__*) self, red, green, blue, alpha);
}

void pFrameBufferSet(PFrameBuffer* self, Int x, Int y, U8 red, U8 green, U8 blue, U8 alpha)
{
    return __pFrameBufferSet__((__PFrameBuffer__*) self, x, y, red, green, blue, alpha);
}

void pFrameBufferBlend(PFrameBuffer* self, Int x, Int y, U8 red, U8 green, U8 blue, U8 alpha)
{
    return __pFrameBufferBlend__((__PFrameBuffer__*) self, x, y, red, green, blue, alpha);
}

void pFrameBufferGet(PFrameBuffer* self, Int x, Int y, U8* red, U8* green, U8* blue, U8* alpha)
{
    return __pFrameBufferGet__((__PFrameBuffer__*) self, x, y, red, green, blue, alpha);
}

#endif // P_SYSTEM_FRAME_BUFFER_H
