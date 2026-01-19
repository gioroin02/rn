#ifndef P_SYSTEM_WIN32_FRAME_BUFFER_C
#define P_SYSTEM_WIN32_FRAME_BUFFER_C

#include "frame_buffer.h"

PWin32FrameBuffer* pWin32FrameBufferReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32FrameBuffer);
}

Bool pWin32FrameBufferCreate(PWin32FrameBuffer* self, Int width, Int height)
{
    pMemorySet(self, sizeof *self, 0xAB);

    BITMAPINFO info;

    pMemorySet(&info.bmiHeader, sizeof info.bmiHeader, 0x00);

    info.bmiHeader.biSize        = sizeof info.bmiHeader;
    info.bmiHeader.biWidth       = width;
    info.bmiHeader.biHeight      = 0 - height;
    info.bmiHeader.biPlanes      = 1;
    info.bmiHeader.biBitCount    = 32;
    info.bmiHeader.biCompression = BI_RGB;

    U32* values = NULL;

    HBITMAP bitmap = CreateDIBSection(NULL, &info,
        DIB_RGB_COLORS, (void**) &values, NULL, 0);

    if (bitmap != NULL) {
        self->bitmap  = bitmap;
        self->values  = values;
        self->width   = width;
        self->height  = height;

        pWin32FrameBufferFill(self, 0, 0, 0, 0xFF);

        return 1;
    }

    return 0;
}

void pWin32FrameBufferDestroy(PWin32FrameBuffer* self)
{
    if (self->bitmap != NULL)
        DeleteObject(self->bitmap);

    pMemorySet(self, sizeof *self, 0xAB);
}

Int pWin32FrameBufferWidth(PWin32FrameBuffer* self)
{
    return self->width;
}

Int pWin32FrameBufferHeight(PWin32FrameBuffer* self)
{
    return self->height;
}

void pWin32FrameBufferFill(PWin32FrameBuffer* self, U8 red, U8 green, U8 blue, U8 alpha)
{
    U32 color = ((U32) blue)  << 0
              | ((U32) green) << 8
              | ((U32) red)   << 16
              | ((U32) alpha) << 24;

    Int row = 0;

    for (row = 0; row < self->height; row += 1) {
        Int col = 0;

        for (col = 0; col < self->width; col += 1)
            self->values[self->width * row + col] = color;
    }
}

void pWin32FrameBufferSet(PWin32FrameBuffer* self, Int x, Int y, U8 red, U8 green, U8 blue, U8 alpha)
{
    U32 color = ((U32) blue)  << 0
              | ((U32) green) << 8
              | ((U32) red)   << 16
              | ((U32) alpha) << 24;

    self->values[self->width * y + x] = color;
}

void pWin32FrameBufferBlend(PWin32FrameBuffer* self, Int x, Int y, U8 red, U8 green, U8 blue, U8 alpha)
{
    U32 color = self->values[self->width * y + x];

    U8 other_blue  = (U8) ((color & 0x000000FF) >> 0);
    U8 other_green = (U8) ((color & 0x0000FF00) >> 8);
    U8 other_red   = (U8) ((color & 0x00FF0000) >> 16);
    U8 other_alpha = (U8) ((color & 0xFF000000) >> 24);

    if (alpha == 0 && other_alpha == 0) return;

    F32 alpha_src = (F32) alpha       / 255.0;
    F32 alpha_dst = (F32) other_alpha / 255.0;

    F32 alpha_res = alpha_src + alpha_dst * (1.0 - alpha_src);

    if (alpha_res <= 0.001) return;

    float red_res   = (red   * alpha_src + other_red   * alpha_dst * (1.0 - alpha_src)) / alpha_res;
    float green_res = (green * alpha_src + other_green * alpha_dst * (1.0 - alpha_src)) / alpha_res;
    float blue_res  = (blue  * alpha_src + other_blue  * alpha_dst * (1.0 - alpha_src)) / alpha_res;

    red   = (U8) red_res   + 0.5;
    green = (U8) green_res + 0.5;
    blue  = (U8) blue_res  + 0.5;
    alpha = (U8) alpha_res * 255.0 + 0.5;

    color = ((U32) blue)  << 0  |
            ((U32) green) << 8  |
            ((U32) red)   << 16 |
            ((U32) alpha) << 24;

    self->values[self->width * y + x] = color;
}

void pWin32FrameBufferGet(PWin32FrameBuffer* self, Int x, Int y, U8* red, U8* green, U8* blue, U8* alpha)
{
    U32 color = self->values[self->width * y + x];

    if (red   != NULL) *blue  = (U8) ((color & 0x000000FF) >> 0);
    if (green != NULL) *green = (U8) ((color & 0x0000FF00) >> 8);
    if (blue  != NULL) *red   = (U8) ((color & 0x00FF0000) >> 16);
    if (alpha != NULL) *alpha = (U8) ((color & 0xFF000000) >> 24);
}

#endif // P_SYSTEM_WIN32_FRAME_BUFFER_C
