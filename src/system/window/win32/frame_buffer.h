#ifndef P_SYSTEM_WIN32_FRAME_BUFFER_H
#define P_SYSTEM_WIN32_FRAME_BUFFER_H

#include "common.h"

typedef struct PWin32FrameBuffer
{
    HBITMAP bitmap;
    U32*    values;
    Int     width;
    Int     height;
}
PWin32FrameBuffer;

PWin32FrameBuffer* pWin32FrameBufferReserve(PMemoryArena* arena);

Bool pWin32FrameBufferCreate(PWin32FrameBuffer* self, Int width, Int height);

void pWin32FrameBufferDestroy(PWin32FrameBuffer* self);

Int pWin32FrameBufferWidth(PWin32FrameBuffer* self);

Int pWin32FrameBufferHeight(PWin32FrameBuffer* self);

void pWin32FrameBufferFill(PWin32FrameBuffer* self, U8 red, U8 green, U8 blue, U8 alpha);

void pWin32FrameBufferSet(PWin32FrameBuffer* self, Int x, Int y, U8 red, U8 green, U8 blue, U8 alpha);

void pWin32FrameBufferBlend(PWin32FrameBuffer* self, Int x, Int y, U8 red, U8 green, U8 blue, U8 alpha);

void pWin32FrameBufferGet(PWin32FrameBuffer* self, Int x, Int y, U8* red, U8* green, U8* blue, U8* alpha);

#endif // P_SYSTEM_WIN32_FRAME_BUFFER_H
