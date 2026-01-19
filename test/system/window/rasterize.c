#ifndef RASTERIZE_C
#define RASTERIZE_C

#include "rasterize.h"

static I64 triangleEdgeCross(I64Vec2 p0, I64Vec2 p1, I64Vec2 p2)
{
    I64Vec2 r01 = i64v2(p1.x - p0.x, p1.y - p0.y);
    I64Vec2 r02 = i64v2(p2.x - p0.x, p2.y - p0.y);

    return r01.x * r02.y - r01.y * r02.x;
}

static I64 triangleEdgeRuleFillBias(I64Vec2 p0, I64Vec2 p1)
{
    I64Vec2 r = i64v2(p1.x - p0.x, p1.y - p0.y);

    if (r.y < 0 || (r.y == 0 && r.x < 0))
        return 1;

    return 0;
}

void paintSegment(PFrameBuffer* buffer, I64Vec2 p0, I64Vec2 p1, U8Vec4 c0, U8Vec4 c1)
{
    Int max_x = pMax(p0.x, p1.x);
    Int min_x = pMin(p0.x, p1.x);
    Int max_y = pMax(p0.y, p1.y);
    Int min_y = pMin(p0.y, p1.y);

    if (max_x - min_x > max_y - min_y) {
        if (p0.x > p1.x) {
            I64Vec2 pt = p0; p0 = p1; p1 = pt;
            U8Vec4  ct = c0; c0 = c1; c1 = ct;
        }

        Int delta_x = p1.x - p0.x;
        Int delta_y = p1.y - p0.y;
        Int dir     = delta_y >= 0 ? +1 : -1;

        delta_y *= dir;

        Int y     = p0.y;
        Int p     = 2 * delta_y - delta_x;
        Int index = 0;

        for (index = 0; index <= delta_x; index += 1) {
            F32 alpha = (F32) index / (F32) delta_x;

            U8Vec4 color = u8v4(
                pClamp(c0.r + alpha * (c1.r - c0.r), 0, 255),
                pClamp(c0.g + alpha * (c1.g - c0.g), 0, 255),
                pClamp(c0.b + alpha * (c1.b - c0.b), 0, 255),
                pClamp(c0.a + alpha * (c1.a - c0.a), 0, 255));

            pFrameBufferSet(buffer, p0.x + index, y,
                color.r, color.g, color.b, color.a);

            y += (p >= 0 ? 1 : 0) * dir;
            p -= (p >= 0 ? 1 : 0) * 2 * delta_x;

            p += 2 * delta_y;
        }
    }
    else {
        if (p0.y > p1.y) {
            I64Vec2 pt = p0; p0 = p1; p1 = pt;
            U8Vec4  ct = c0; c0 = c1; c1 = ct;
        }

        Int delta_x = p1.x - p0.x;
        Int delta_y = p1.y - p0.y;
        Int dir     = delta_x >= 0 ? +1 : -1;

        delta_x *= dir;

        Int x     = p0.x;
        Int p     = 2 * delta_x - delta_y;
        Int index = 0;

        for (index = 0; index <= delta_y; index += 1) {
            F32 alpha = (F32) index / (F32) delta_y;

            U8Vec4 color = u8v4(
                pClamp(c0.r + alpha * (c1.r - c0.r), 0, 255),
                pClamp(c0.g + alpha * (c1.g - c0.g), 0, 255),
                pClamp(c0.b + alpha * (c1.b - c0.b), 0, 255),
                pClamp(c0.a + alpha * (c1.a - c0.a), 0, 255));

            pFrameBufferSet(buffer, x, p0.y + index,
                color.r, color.g, color.b, color.a);

            x += (p >= 0 ? 1 : 0) * dir;
            p -= (p >= 0 ? 1 : 0) * 2 * delta_y;

            p += 2 * delta_x;
        }
    }
}

void paintTriangleFrame(PFrameBuffer* buffer, I64Vec2 p0, I64Vec2 p1, I64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2)
{
    paintSegment(buffer, p0, p1, c0, c1);
    paintSegment(buffer, p1, p2, c1, c2);
    paintSegment(buffer, p2, p0, c2, c0);
}

void paintTriangle(PFrameBuffer* buffer, I64Vec2 p0, I64Vec2 p1, I64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2)
{
    Int max_x = pMax(p0.x, pMax(p1.x, p2.x));
    Int min_x = pMin(p0.x, pMin(p1.x, p2.x));
    Int max_y = pMax(p0.y, pMax(p1.y, p2.y));
    Int min_y = pMin(p0.y, pMin(p1.y, p2.y));

    max_x = pClamp(max_x, 0, pFrameBufferWidth(buffer));
    min_x = pClamp(min_x, 0, pFrameBufferWidth(buffer));
    max_y = pClamp(max_y, 0, pFrameBufferHeight(buffer));
    min_y = pClamp(min_y, 0, pFrameBufferHeight(buffer));

    Int area = triangleEdgeCross(p0, p1, p2);

    I64Vec2 point = i64v2(min_x, min_y);

    Int b0 = triangleEdgeRuleFillBias(p1, p2);
    Int b1 = triangleEdgeRuleFillBias(p2, p0);
    Int b2 = triangleEdgeRuleFillBias(p0, p1);

    for (point.y = min_y; point.y <= max_y; point.y += 1) {
        for (point.x = min_x; point.x <= max_x; point.x += 1) {
            Int w0 = triangleEdgeCross(p1, p2, point) - b0;
            Int w1 = triangleEdgeCross(p2, p0, point) - b1;
            Int w2 = triangleEdgeCross(p0, p1, point) - b2;

            if ((w0 | w1 | w2) >= 0) {
                F32 alpha = (F32) w0 / (F32) area;
                F32 beta  = (F32) w1 / (F32) area;
                F32 gamma = (F32) w2 / (F32) area;

                U8Vec4 color = u8v4(
                    pClamp(alpha * c0.r + beta * c1.r + gamma * c2.r, 0, 255),
                    pClamp(alpha * c0.g + beta * c1.g + gamma * c2.g, 0, 255),
                    pClamp(alpha * c0.b + beta * c1.b + gamma * c2.b, 0, 255),
                    pClamp(alpha * c0.a + beta * c1.a + gamma * c2.a, 0, 255));

                pFrameBufferSet(buffer, point.x, point.y,
                    color.r, color.g, color.b, color.a);
            }
        }
    }
}

void paintRectangleFrame(PFrameBuffer* buffer, I64Vec2 origin, I64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3)
{
    I64Vec2 p0 = i64v2(origin.x - size.x / 2, origin.y - size.y / 2);
    I64Vec2 p1 = i64v2(origin.x + size.x / 2, origin.y - size.y / 2);
    I64Vec2 p2 = i64v2(origin.x - size.x / 2, origin.y + size.y / 2);
    I64Vec2 p3 = i64v2(origin.x + size.x / 2, origin.y + size.y / 2);

    paintTriangleFrame(buffer, p0, p1, p2, c0, c1, c2);
    paintTriangleFrame(buffer, p3, p2, p1, c3, c2, c1);
}

void paintRectangle(PFrameBuffer* buffer, I64Vec2 origin, I64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3)
{
    I64Vec2 p0 = i64v2(origin.x - size.x / 2, origin.y - size.y / 2);
    I64Vec2 p1 = i64v2(origin.x + size.x / 2, origin.y - size.y / 2);
    I64Vec2 p2 = i64v2(origin.x - size.x / 2, origin.y + size.y / 2);
    I64Vec2 p3 = i64v2(origin.x + size.x / 2, origin.y + size.y / 2);

    paintTriangle(buffer, p0, p1, p2, c0, c1, c2);
    paintTriangle(buffer, p3, p2, p1, c3, c2, c1);
}

#endif // RASTERIZE_C
