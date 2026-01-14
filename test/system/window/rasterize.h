#ifndef RASTERIZE_H
#define RASTERIZE_H

#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/time/export.h"
#include "../../../src/system/window/export.h"

#include "vector/export.h"

void paintSegment(PxBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, U8Vec4 c0, U8Vec4 c1);

void paintTriangleFrame(PxBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, S64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2);

void paintTriangle(PxBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, S64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2);

void paintRectangleFrame(PxBitmap* bitmap, S64Vec2 origin, S64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3);

void paintRectangle(PxBitmap* bitmap, S64Vec2 origin, S64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3);

#endif // RASTERIZE_H
