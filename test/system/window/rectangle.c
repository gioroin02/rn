#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/time/export.h"
#include "../../../src/system/window/export.h"

#include "vector/export.h"

#include <stdio.h>
#include <math.h>

typedef struct Context
{
    PxWindow* window;
    PxBitmap* bitmap;
    PxClock*  clock;

    f32 ticks;
    f32 time;
    b32 active;
}
Context;

void swap(void* pntr, ssize size, void* other)
{
    ssize index = 0;

    for (index = 0; index < size; index += 1) {
        ((u8*) pntr)[index]  ^= ((u8*) other)[index];
        ((u8*) other)[index] ^= ((u8*) pntr)[index];
        ((u8*) pntr)[index]  ^= ((u8*) other)[index];
    }
}

void paintLine(PxBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, U8Vec4 color)
{
    ssize max_x   = pxMax(p0.x, p1.x);
    ssize min_x   = pxMin(p0.x, p1.x);
    ssize max_y   = pxMax(p0.y, p1.y);
    ssize min_y   = pxMin(p0.y, p1.y);

    if (max_x - min_x > max_y - min_y) {
        if (p0.x > p1.x) swap(&p0, sizeof p0, &p1);

        ssize delta_x = p1.x - p0.x;
        ssize delta_y = p1.y - p0.y;
        ssize dir     = delta_y >= 0 ? +1 : -1;

        delta_y *= dir;

        ssize y     = p0.y;
        ssize p     = 2 * delta_y - delta_x;
        ssize index = 0;

        for (index = 0; index <= delta_x; index += 1) {
            pxBitmapPixelSet(bitmap, p0.x + index, y,
                color.r, color.g, color.b, color.a);

            y += (p >= 0 ? 1 : 0) * dir;
            p -= (p >= 0 ? 1 : 0) * 2 * delta_x;

            p += 2 * delta_y;
        }
    }
    else {
        if (p0.y > p1.y) swap(&p0, sizeof p0, &p1);

        ssize delta_x = p1.x - p0.x;
        ssize delta_y = p1.y - p0.y;
        ssize dir     = delta_x >= 0 ? +1 : -1;

        delta_x *= dir;

        ssize x     = p0.x;
        ssize p     = 2 * delta_x - delta_y;
        ssize index = 0;

        for (index = 0; index <= delta_y; index += 1) {
            pxBitmapPixelSet(bitmap, x, p0.y + index,
                color.r, color.g, color.b, color.a);

            x += (p >= 0 ? 1 : 0) * dir;
            p -= (p >= 0 ? 1 : 0) * 2 * delta_y;

            p += 2 * delta_x;
        }
    }
}

s64 triangleEdgeCross(S64Vec2 p0, S64Vec2 p1, S64Vec2 p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

b32 triangleEdgeIsTopLeft(S64Vec2 p0, S64Vec2 p1)
{
    if (p1.x - p0.x < 0) return 0;
    if (p1.y - p0.y > 0) return 1;

    return 0;
}

void paintTriangleLines(PxBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, S64Vec2 p2, U8Vec4 color)
{
    paintLine(bitmap, p0, p1, color);
    paintLine(bitmap, p1, p2, color);
    paintLine(bitmap, p2, p0, color);
}

void paintTriangle(PxBitmap* bitmap, S64Vec2 p0, S64Vec2 p1, S64Vec2 p2, U8Vec4 c0, U8Vec4 c1, U8Vec4 c2)
{
    s64 max_x = pxMax(p0.x, pxMax(p1.x, p2.x));
    s64 min_x = pxMin(p0.x, pxMin(p1.x, p2.x));
    s64 max_y = pxMax(p0.y, pxMax(p1.y, p2.y));
    s64 min_y = pxMin(p0.y, pxMin(p1.y, p2.y));

    s64 area = triangleEdgeCross(p0, p1, p2);

    S64Vec2 point = s64Vec2(min_x, min_y);

    s64 b0 = triangleEdgeIsTopLeft(p1, p2) != 0 ? 1 : 0;
    s64 b1 = triangleEdgeIsTopLeft(p2, p0) != 0 ? 1 : 0;
    s64 b2 = triangleEdgeIsTopLeft(p0, p1) != 0 ? 1 : 0;

    for (point.y = min_y; point.y <= max_y; point.y += 1) {
        for (point.x = min_x; point.x <= max_x; point.x += 1) {
            s64 w0 = triangleEdgeCross(p1, p2, point) - b0;
            s64 w1 = triangleEdgeCross(p2, p0, point) - b1;
            s64 w2 = triangleEdgeCross(p0, p1, point) - b2;

            if ((w0 | w1 | w2) >= 0) {
                f32 alpha = (f32) w0 / (f32) area;
                f32 beta  = (f32) w1 / (f32) area;
                f32 gamma = (f32) w2 / (f32) area;

                S64Vec4 color = s64Vec4(
                    alpha * c0.r + beta * c1.r + gamma * c2.r,
                    alpha * c0.g + beta * c1.g + gamma * c2.g,
                    alpha * c0.b + beta * c1.b + gamma * c2.b,
                    0xFF // alpha * ((f32) c0.a) / 255 + beta * ((f32) c1.a) / 255 + gamma * ((f32) c2.a) / 255
                );

                pxBitmapPixelSet(bitmap, point.x, point.y,
                    color.r, color.g, color.b, color.a);
            }
        }
    }
}

void paintRectangleLines(PxBitmap* bitmap, S64Vec2 origin, S64Vec2 size, U8Vec4 color)
{
    S64Vec2 p0 = s64Vec2(origin.x - size.x / 2, origin.y - size.y / 2);
    S64Vec2 p1 = s64Vec2(origin.x + size.x / 2, origin.y - size.y / 2);
    S64Vec2 p2 = s64Vec2(origin.x - size.x / 2, origin.y + size.y / 2);
    S64Vec2 p3 = s64Vec2(origin.x + size.x / 2, origin.y + size.y / 2);

    paintTriangleLines(bitmap, p0, p1, p2, color);
    paintTriangleLines(bitmap, p3, p2, p1, color);
}

void paintRectangle(PxBitmap* bitmap, S64Vec2 origin, S64Vec2 size, U8Vec4 color)
{
    S64Vec2 p0 = s64Vec2(origin.x - size.x / 2, origin.y - size.y / 2);
    S64Vec2 p1 = s64Vec2(origin.x + size.x / 2, origin.y - size.y / 2);
    S64Vec2 p2 = s64Vec2(origin.x - size.x / 2, origin.y + size.y / 2);
    S64Vec2 p3 = s64Vec2(origin.x + size.x / 2, origin.y + size.y / 2);

    paintTriangle(bitmap, p0, p1, p2, u8Vec4(0xFF, 0, 0, 0), u8Vec4(0, 0xFF, 0, 0), u8Vec4(0, 0, 0xFF, 0));
    paintTriangle(bitmap, p3, p2, p1, u8Vec4(0xFF, 0, 0, 0), u8Vec4(0, 0, 0xFF, 0), u8Vec4(0, 0xFF, 0, 0));
}

void contextUpdate(Context* self)
{
    f32 elapsed = pxClockElapsed(self->clock);

    self->ticks += elapsed;
    self->time  += elapsed;

    pxWindowClear(self->window, 0x0F, 0x0F, 0x0F);

    f32 delta_sin = sin(self->ticks * 5);
    f32 delta_cos = cos(self->ticks * 5);

    pxBitmapFill(self->bitmap, 0x08, 0x08, 0x08, 0xFF);

    paintTriangle(self->bitmap,
        s64Vec2(100 + delta_sin * 5, 50 + delta_cos * 5),
        s64Vec2(50 + delta_cos * 5, 100 + delta_sin * 5),
        s64Vec2(50 + delta_cos * 5, 50 + delta_sin * 5),
        u8Vec4(0xFF, 0, 0, 0xFF),
        u8Vec4(0, 0xFF, 0, 0xFF),
        u8Vec4(0, 0, 0xFF, 0xFF));

    paintRectangleLines(self->bitmap,
        s64Vec2(150 + delta_sin * 5, 150 + delta_sin * 5),
        s64Vec2(100 + delta_cos * 5, 150 + delta_cos * 5),
        u8Vec4(0xBE, 0x0A, 0xFF, 0xFF));

    paintLine(self->bitmap,
        s64Vec2(300 + delta_cos * 5, 0),
        s64Vec2(0, 300 + delta_sin * 5),
        u8Vec4(0x14, 0x7D, 0xF5, 0xFF));

    ssize width  = pxBitmapWidth(self->bitmap);
    ssize height = pxBitmapHeight(self->bitmap);
    ssize x      = pxWindowWidthGet(self->window) / 2 - width / 2;
    ssize y      = pxWindowHeightGet(self->window) / 2 - height / 2;

    pxWindowPaint(self->window, 0, 0, width, height, self->bitmap);

    pxWindowFlush(self->window);
}

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(8));

    Context context;

    pxMemorySet(&context, sizeof context, 0xAB);

    context.window = pxWindowReserve(&arena);
    context.bitmap = pxBitmapReserve(&arena);
    context.clock  = pxClockReserve(&arena);
    context.ticks  = 0;
    context.active = 1;

    pxWindowCreate(context.window, pxString8("Prova"), 1600, 900, 4);
    pxBitmapCreate(context.bitmap, &arena, 800, 800);
    pxClockCreate(context.clock);

    pxWindowPntrContextSet(context.window, &context);
    pxWindowProcUpdateSet(context.window, contextUpdate);
    pxWindowVisibilitySet(context.window, PxWindowVisibility_Show);

    while (context.active != 0) {
        PxWindowEvent event;

        pxMemorySet(&event, sizeof event, 0xAB);

        while (pxWindowPollEvent(context.window, &event) != 0) {
            switch (event.kind) {
                case PxWindowEvent_Quit: context.active = 0; break;

                case PxWindowEvent_KeyboardKey: {
                    PxWindowKeyboardKey key     = event.keyboard_key.key;
                    b32                 pressed = event.keyboard_key.pressed;

                    if (pressed != 0 && key == PxWindowKeyboardKey_Escape)
                        context.active = 0;
                } break;

                default: break;
            }

            pxMemorySet(&event, sizeof event, 0xAB);
        }

        contextUpdate(&context);
    }

    pxWindowDestroy(context.window);
}
