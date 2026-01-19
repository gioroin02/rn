#ifndef RASTERIZE_H
#define RASTERIZE_H

#include "vector/export.h"

#include "../../../src/system/window/export.h"

void paintSegment(PFrameBuffer* buffer, I64Vec2 p0, I64Vec2 p1, U8Vec4 c0, U8Vec4 c1);

void paintTriangleFrame(PFrameBuffer* buffer, I64Vec2 p0, I64Vec2 p1, I64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2);

void paintTriangle(PFrameBuffer* buffer, I64Vec2 p0, I64Vec2 p1, I64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2);

void paintRectangleFrame(PFrameBuffer* buffer, I64Vec2 origin, I64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3);

void paintRectangle(PFrameBuffer* buffer, I64Vec2 origin, I64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3);

#endif // RASTERIZE_H
