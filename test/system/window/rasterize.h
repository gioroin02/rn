#ifndef RASTERIZE_H
#define RASTERIZE_H

#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/time/export.h"
#include "../../../src/system/window/export.h"

#include "vector/export.h"

void paintSegment(PBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, U8Vec4 c0, U8Vec4 c1);

void paintTriangleFrame(PBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, S64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2);

void paintTriangle(PBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, S64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2);

void paintRectangleFrame(PBitmap* bitmap, S64Vec2 origin, S64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3);

void paintRectangle(PBitmap* bitmap, S64Vec2 origin, S64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3);

#endif // RASTERIZE_H
