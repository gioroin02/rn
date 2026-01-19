#ifndef P_SYSTEM_FRAME_BUFFER_H
#define P_SYSTEM_FRAME_BUFFER_H

#include "import.h"

typedef struct PFrameBuffer { U8 __private__; } PFrameBuffer;

PFrameBuffer* pFrameBufferReserve(PMemoryArena* arena);

Bool pFrameBufferCreate(PFrameBuffer* self, Int width, Int height);

Int pFrameBufferWidth(PFrameBuffer* self);

Int pFrameBufferHeight(PFrameBuffer* self);

void pFrameBufferFill(PFrameBuffer* self, U8 red, U8 green, U8 blue, U8 alpha);

void pFrameBufferSet(PFrameBuffer* self, Int x, Int y, U8 red, U8 green, U8 blue, U8 alpha);

void pFrameBufferBlend(PFrameBuffer* self, Int x, Int y, U8 red, U8 green, U8 blue, U8 alpha);

void pFrameBufferGet(PFrameBuffer* self, Int x, Int y, U8* red, U8* green, U8* blue, U8* alpha);

#endif // P_SYSTEM_FRAME_BUFFER_H
