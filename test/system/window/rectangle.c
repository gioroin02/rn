#include "../../../src/string/export.h"
#include "../../../src/system/memory/export.h"
#include "../../../src/system/time/export.h"
#include "../../../src/system/window/export.h"

#include <stdio.h>
#include <math.h>

void swap(void* pntr, ssize size, void* other)
{
    ssize index = 0;

    for (index = 0; index < size; index += 1) {
        ((u8*) pntr)[index]  ^= ((u8*) other)[index];
        ((u8*) other)[index] ^= ((u8*) pntr)[index];
        ((u8*) pntr)[index]  ^= ((u8*) other)[index];
    }
}

typedef union u8vec4
{
    u8  values[4];
    u32 v03;

    struct
    {
        u8 x, y, z, w;
    };

    struct
    {
        u8 r, g, b, a;
    };

    struct
    {
        u8 v0, v1, v2, v3;
    };

    struct
    {
        u16 v01, v23;
    };
}
u8vec4;

u8vec4 u8v4(u8 v0, u8 v1, u8 v2, u8 v3)
{
    u8vec4 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;
    result.v2 = v2;
    result.v3 = v3;

    return result;
}

typedef union svec2
{
    ssize values[4];

    struct
    {
        ssize x, y;
    };

    struct
    {
        ssize r, g;
    };

    struct
    {
        ssize v0, v1;
    };
}
svec2;

svec2 sv2(ssize v0, ssize v1)
{
    svec2 result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.v0 = v0;
    result.v1 = v1;

    return result;
}

typedef struct Context
{
    PxWindow*        window;
    PxWindowSurface* surface;
    PxClock*         clock;

    f32 ticks;
    f32 time;
    b32 active;
}
Context;

u8vec4 blend(u8vec4 c0, u8vec4 c1)
{
    usize one_minus_alpha = 255 - c0.a;
    usize alpha           = c0.a + c1.a * one_minus_alpha;

    usize red   = (c0.r * c0.a + c1.r * c1.a * one_minus_alpha) / alpha;
    usize green = (c0.g * c0.a + c1.g * c1.a * one_minus_alpha) / alpha;
    usize blue  = (c0.b * c0.a + c1.b * c1.a * one_minus_alpha) / alpha;

    return u8v4(red, green, blue, alpha);
}

void paintLineHor(PxWindowSurface* surface, svec2 p0, svec2 p1, u8vec4 color)
{
    if (p0.x > p1.x) swap(&p0, sizeof p0, &p1);

    ssize delta_x = p1.x - p0.x;
    ssize delta_y = p1.y - p0.y;
    ssize dir     = delta_y >= 0 ? 1 : -1;

    delta_y *= dir;

    if (delta_x != 0) {
        ssize y = p0.y;
        ssize p = 2 * delta_y - delta_x;

        ssize index = 0;

        for (index = 0; index <= delta_x; index += 1) {
            pxWindowSurfacePixelSet(surface, p0.x + index, y,
                color.r, color.g, color.b, color.a);

            if (p >= 0) {
                y += dir;
                p -= 2 * delta_x;
            }

            p += 2 * delta_y;
        }
    }
    else pxWindowSurfacePixelSet(surface, p0.x, p0.y,
        color.r, color.g, color.b, color.a);
}

void paintLineVer(PxWindowSurface* surface, svec2 p0, svec2 p1, u8vec4 color)
{
    if (p0.y > p1.y) swap(&p0, sizeof p0, &p1);

    ssize delta_x = p1.x - p0.x;
    ssize delta_y = p1.y - p0.y;
    ssize dir     = delta_x >= 0 ? 1 : -1;

    delta_x *= dir;

    if (delta_y != 0) {
        ssize x = p0.x;
        ssize p = 2 * delta_x - delta_y;

        ssize index = 0;

        for (index = 0; index <= delta_y; index += 1) {
            pxWindowSurfacePixelSet(surface, x, p0.y + index,
                color.r, color.g, color.b, 0xFF);

            if (p >= 0) {
                x += dir;
                p -= 2 * delta_y;
            }

            p += 2 * delta_x;
        }
    }
    else pxWindowSurfacePixelSet(surface, p0.x, p0.y,
        color.r, color.g, color.b, 0xFF);
}

void paintLine(PxWindowSurface* surface, svec2 p0, svec2 p1, u8vec4 color)
{
    /*
    p0.x = pxClamp(p0.x, 0, pxWindowSurfaceWidth(surface));
    p1.x = pxClamp(p1.x, 0, pxWindowSurfaceWidth(surface));
    p0.y = pxClamp(p0.y, 0, pxWindowSurfaceHeight(surface));
    p1.y = pxClamp(p1.y, 0, pxWindowSurfaceHeight(surface));
    */

    ssize delta_x = pxMax(p0.x, p1.x) - pxMin(p0.x, p1.x);
    ssize delta_y = pxMax(p0.y, p1.y) - pxMin(p0.y, p1.y);

    if (delta_x > delta_y)
        paintLineHor(surface, p0, p1, color);
    else
        paintLineVer(surface, p0, p1, color);
}

void paintTriangleLines(PxWindowSurface* surface, svec2 p0, svec2 p1, svec2 p2, u8vec4 color)
{
    paintLine(surface, p0, p1, color);
    paintLine(surface, p1, p2, color);
    paintLine(surface, p2, p0, color);
}

void paintTriangle(PxWindowSurface* surface, svec2 p0, svec2 p1, svec2 p2, u8vec4 color)
{
    
}

void paintRectangleLines(PxWindowSurface* surface, svec2 origin, svec2 size, u8vec4 color)
{
    svec2 p0 = sv2(origin.x - size.x / 2, origin.y - size.y / 2);
    svec2 p1 = sv2(origin.x + size.x / 2, origin.y - size.y / 2);
    svec2 p2 = sv2(origin.x - size.x / 2, origin.y + size.y / 2);
    svec2 p3 = sv2(origin.x + size.x / 2, origin.y + size.y / 2);

    paintTriangleLines(surface, p0, p1, p2, color);
    paintTriangleLines(surface, p1, p2, p3, color);
}

void paintRectangle(PxWindowSurface* surface, svec2 origin, svec2 size, u8vec4 color)
{
    svec2 p0 = sv2(origin.x - size.x / 2, origin.y - size.y / 2);
    svec2 p1 = sv2(origin.x + size.x / 2, origin.y - size.y / 2);
    svec2 p2 = sv2(origin.x - size.x / 2, origin.y + size.y / 2);
    svec2 p3 = sv2(origin.x + size.x / 2, origin.y + size.y / 2);

    paintTriangle(surface, p0, p1, p2, color);
    paintTriangle(surface, p1, p2, p3, color);
}

void paintGradient(PxWindowSurface* surface, ssize offset_x, ssize offset_y)
{
    ssize col = 0;
    ssize row = 0;

    for (col = 0; col < pxWindowSurfaceWidth(surface); col += 1) {
        for (row = 0; row < pxWindowSurfaceHeight(surface); row += 1) {
            u32 red   = col + offset_x;
            u32 blue  = row + offset_y;
            u32 green = (red + blue) / 4;

            pxWindowSurfacePixelSet(surface, col, row, red, green, blue, 0);
        }
    }
}

void contextUpdate(Context* self)
{
    f32 elapsed = pxClockElapsed(self->clock);

    self->ticks += elapsed;
    self->time  += elapsed;

    // if (self->time >= 0.0166f) {
        // self->time -= 0.0166f;

        pxWindowClear(self->window, 0x0F, 0x0F, 0x0F);

        f32 delta_sin = sin(self->ticks * 10) * 10;
        f32 delta_cos = cos(self->ticks * 10) * 10;

        pxWindowSurfaceFill(self->surface, 0x08, 0x08, 0x08, 0xFF);

        paintTriangleLines(self->surface,
            sv2(300 + delta_sin, 100 + delta_cos),
            sv2(300 + delta_cos, 300 + delta_sin),
            sv2(400 + delta_sin, 100 + delta_cos),
            u8v4(0xFF, 0, 0, 0xFF));

        paintRectangleLines(self->surface,
            sv2(500 + delta_sin, 500 + delta_sin),
            sv2(100 + delta_cos, 150 + delta_cos),
            u8v4(0xBE, 0x0A, 0xFF, 0xFF));

        paintLine(self->surface, sv2(800, 0), sv2(0, 800),
            u8v4(0x14, 0x7D, 0xF5, 0xFF));

        ssize width  = pxWindowSurfaceWidth(self->surface);
        ssize height = pxWindowSurfaceHeight(self->surface);
        ssize x      = pxWindowWidthGet(self->window) / 2 - width / 2;
        ssize y      = pxWindowHeightGet(self->window) / 2 - height / 2;

        pxWindowPaint(self->window, x, y, width, height, self->surface);

        pxWindowFlush(self->window);
     // }
}

int main(int argc, char** argv)
{
    PxMemoryArena arena = pxSystemMemoryReserve(pxMemoryMIB(8));

    Context context;

    pxMemorySet(&context, sizeof context, 0xAB);

    context.window  = pxWindowReserve(&arena);
    context.surface = pxWindowSurfaceReserve(&arena);
    context.clock   = pxClockReserve(&arena);
    context.ticks   = 0;
    context.active  = 1;

    pxWindowCreate(context.window, pxString8("Prova"), 1600, 900);

    pxWindowSurfaceCreate(context.surface, &arena, 800, 800);

    pxClockCreate(context.clock);

    pxWindowClear(context.window, 0, 0, 0);

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
