#ifndef RASTERIZE_C
#define RASTERIZE_C

#include "rasterize.h"

static s64 triangleEdgeCross(S64Vec2 p0, S64Vec2 p1, S64Vec2 p2)
{
    S64Vec2 r01 = s64Vec2(p1.x - p0.x, p1.y - p0.y);
    S64Vec2 r02 = s64Vec2(p2.x - p0.x, p2.y - p0.y);

    return r01.x * r02.y - r01.y * r02.x;
}

static s64 triangleEdgeRuleFillBias(S64Vec2 p0, S64Vec2 p1)
{
    S64Vec2 r = s64Vec2(p1.x - p0.x, p1.y - p0.y);

    if (r.y < 0 || (r.y == 0 && r.x < 0))
        return 1;

    return 0;
}

void paintSegment(PBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, U8Vec4 c0, U8Vec4 c1)
{
    ssize max_x = pMax(p0.x, p1.x);
    ssize min_x = pMin(p0.x, p1.x);
    ssize max_y = pMax(p0.y, p1.y);
    ssize min_y = pMin(p0.y, p1.y);

    if (max_x - min_x > max_y - min_y) {
        if (p0.x > p1.x) {
            S64Vec2 pt = p0; p0 = p1; p1 = pt;
            U8Vec4  ct = c0; c0 = c1; c1 = ct;
        }

        ssize delta_x = p1.x - p0.x;
        ssize delta_y = p1.y - p0.y;
        ssize dir     = delta_y >= 0 ? +1 : -1;

        delta_y *= dir;

        ssize y     = p0.y;
        ssize p     = 2 * delta_y - delta_x;
        ssize index = 0;

        for (index = 0; index <= delta_x; index += 1) {
            f32 alpha = (f32) index / (f32) delta_x;

            U8Vec4 color = u8Vec4(
                pClamp(c0.r + alpha * (c1.r - c0.r), 0, 255),
                pClamp(c0.g + alpha * (c1.g - c0.g), 0, 255),
                pClamp(c0.b + alpha * (c1.b - c0.b), 0, 255),
                pClamp(c0.a + alpha * (c1.a - c0.a), 0, 255));

            pBitmapPixelSet(bitmap, p0.x + index, y,
                color.r, color.g, color.b, color.a);

            y += (p >= 0 ? 1 : 0) * dir;
            p -= (p >= 0 ? 1 : 0) * 2 * delta_x;

            p += 2 * delta_y;
        }
    }
    else {
        if (p0.y > p1.y) {
            S64Vec2 pt = p0; p0 = p1; p1 = pt;
            U8Vec4  ct = c0; c0 = c1; c1 = ct;
        }

        ssize delta_x = p1.x - p0.x;
        ssize delta_y = p1.y - p0.y;
        ssize dir     = delta_x >= 0 ? +1 : -1;

        delta_x *= dir;

        ssize x     = p0.x;
        ssize p     = 2 * delta_x - delta_y;
        ssize index = 0;

        for (index = 0; index <= delta_y; index += 1) {
            f32 alpha = (f32) index / (f32) delta_y;

            U8Vec4 color = u8Vec4(
                pClamp(c0.r + alpha * (c1.r - c0.r), 0, 255),
                pClamp(c0.g + alpha * (c1.g - c0.g), 0, 255),
                pClamp(c0.b + alpha * (c1.b - c0.b), 0, 255),
                pClamp(c0.a + alpha * (c1.a - c0.a), 0, 255));

            pBitmapPixelSet(bitmap, x, p0.y + index,
                color.r, color.g, color.b, color.a);

            x += (p >= 0 ? 1 : 0) * dir;
            p -= (p >= 0 ? 1 : 0) * 2 * delta_y;

            p += 2 * delta_x;
        }
    }
}

void paintTriangleFrame(PBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, S64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2)
{
    paintSegment(bitmap, p0, p1, c0, c1);
    paintSegment(bitmap, p1, p2, c1, c2);
    paintSegment(bitmap, p2, p0, c2, c0);
}

void paintTriangle(PBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, S64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2)
{
    s64 max_x = pMax(p0.x, pMax(p1.x, p2.x));
    s64 min_x = pMin(p0.x, pMin(p1.x, p2.x));
    s64 max_y = pMax(p0.y, pMax(p1.y, p2.y));
    s64 min_y = pMin(p0.y, pMin(p1.y, p2.y));

    s64 area = triangleEdgeCross(p0, p1, p2);

    S64Vec2 point = s64Vec2(min_x, min_y);

    s64 b0 = triangleEdgeRuleFillBias(p1, p2);
    s64 b1 = triangleEdgeRuleFillBias(p2, p0);
    s64 b2 = triangleEdgeRuleFillBias(p0, p1);

    for (point.y = min_y; point.y <= max_y; point.y += 1) {
        for (point.x = min_x; point.x <= max_x; point.x += 1) {
            s64 w0 = triangleEdgeCross(p1, p2, point) - b0;
            s64 w1 = triangleEdgeCross(p2, p0, point) - b1;
            s64 w2 = triangleEdgeCross(p0, p1, point) - b2;

            if ((w0 | w1 | w2) >= 0) {
                f32 alpha = (f32) w0 / (f32) area;
                f32 beta  = (f32) w1 / (f32) area;
                f32 gamma = (f32) w2 / (f32) area;

                U8Vec4 color = u8Vec4(
                    pClamp(alpha * c0.r + beta * c1.r + gamma * c2.r, 0, 255),
                    pClamp(alpha * c0.g + beta * c1.g + gamma * c2.g, 0, 255),
                    pClamp(alpha * c0.b + beta * c1.b + gamma * c2.b, 0, 255),
                    pClamp(alpha * c0.a + beta * c1.a + gamma * c2.a, 0, 255));

                pBitmapPixelSet(bitmap, point.x, point.y,
                    color.r, color.g, color.b, color.a);
            }
        }
    }
}

void paintRectangleFrame(PBitmap* bitmap, S64Vec2 origin, S64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3)
{
    S64Vec2 p0 = s64Vec2(origin.x - size.x / 2, origin.y - size.y / 2);
    S64Vec2 p1 = s64Vec2(origin.x + size.x / 2, origin.y - size.y / 2);
    S64Vec2 p2 = s64Vec2(origin.x - size.x / 2, origin.y + size.y / 2);
    S64Vec2 p3 = s64Vec2(origin.x + size.x / 2, origin.y + size.y / 2);

    paintTriangleFrame(bitmap, p0, p1, p2, c0, c1, c2);
    paintTriangleFrame(bitmap, p3, p2, p1, c3, c2, c1);
}

void paintRectangle(PBitmap* bitmap, S64Vec2 origin, S64Vec2 size, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2, U8Vec4 c3)
{
    S64Vec2 p0 = s64Vec2(origin.x - size.x / 2, origin.y - size.y / 2);
    S64Vec2 p1 = s64Vec2(origin.x + size.x / 2, origin.y - size.y / 2);
    S64Vec2 p2 = s64Vec2(origin.x - size.x / 2, origin.y + size.y / 2);
    S64Vec2 p3 = s64Vec2(origin.x + size.x / 2, origin.y + size.y / 2);

    paintTriangle(bitmap, p0, p1, p2, c0, c1, c2);
    paintTriangle(bitmap, p3, p2, p1, c3, c2, c1);
}

#endif // RASTERIZE_C
