#ifndef P_SYSTEM_WIN32_WINDOW_OPENGL_WINDOW_C
#define P_SYSTEM_WIN32_WINDOW_OPENGL_WINDOW_C

#include "window.h"

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB         0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB  0x9126

#define WGL_CONTEXT_PROFILE_CORE_ARB          1
#define WGL_CONTEXT_PROFILE_COMPATIBILITY_ARB 2

#define WGL_CONTEXT_DEBUG_BIT_ARB 1

#define WGL_PIXEL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_PIXEL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_PIXEL_DOUBLE_BUFFER_ARB  0x2011
#define WGL_PIXEL_TYPE_ARB           0x2013
#define WGL_PIXEL_COLOR_BITS_ARB     0x2014
#define WGL_PIXEL_DEPTH_BITS_ARB     0x2022
#define WGL_PIXEL_STENCIL_BITS_ARB   0x2023
#define WGL_PIXEL_SAMPLE_BUFFERS_ARB 0x2041
#define WGL_PIXEL_SAMPLES_ARB        0x2042

#define WGL_PIXEL_TYPE_RGBA_ARB 1

static int pWin32OpenglProfile(POpenglProfile profile)
{
    switch (profile) {
        case POpenglProfile_Compatibility:
            return WGL_CONTEXT_PROFILE_COMPATIBILITY_ARB;

        case POpenglProfile_Core:
            return WGL_CONTEXT_PROFILE_CORE_ARB;

        default: break;
    }

    return 0;
}

static int pWin32OpenglFlag(POpenglContextFlag flag)
{
    int result = 0;

    if ((flag & POpenglContextFlag_Debug) != 0)
        result |= WGL_CONTEXT_DEBUG_BIT_ARB;

    return result;
}

static HGLRC pWin32OpenglCreate(HDC device, POpenglContextAttribs attribs)
{
    int attribs_context[32];
    int attribs_pixel[32];

    pMemorySet(attribs_context, sizeof attribs_context, 0x00);
    pMemorySet(attribs_pixel,   sizeof attribs_pixel,   0x00);

    int config_context[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, attribs.version_major,
        WGL_CONTEXT_MINOR_VERSION_ARB, attribs.version_minor,
        WGL_CONTEXT_PROFILE_MASK_ARB,  pWin32OpenglProfile(attribs.profile),
        WGL_CONTEXT_FLAGS_ARB,         pWin32OpenglFlag(attribs.flag),
    };

    int config_pixel[] = {
        WGL_PIXEL_DRAW_TO_WINDOW_ARB, 1,
        WGL_PIXEL_SUPPORT_OPENGL_ARB, 1,
        WGL_PIXEL_DOUBLE_BUFFER_ARB,  1,
        WGL_PIXEL_TYPE_ARB,           WGL_PIXEL_TYPE_RGBA_ARB,
        WGL_PIXEL_COLOR_BITS_ARB,     32,
        WGL_PIXEL_DEPTH_BITS_ARB,     24,
        WGL_PIXEL_STENCIL_BITS_ARB,   8,
    };

    pMemoryCopy(attribs_context, sizeof config_context, config_context);
    pMemoryCopy(attribs_pixel,     sizeof config_pixel,   config_pixel);

    PIXELFORMATDESCRIPTOR descr;

    pMemorySet(&descr, sizeof descr, 0x00);

    descr.nSize        = sizeof descr;
    descr.nVersion     = 1;
    descr.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    descr.iPixelType   = PFD_TYPE_RGBA;
    descr.iLayerType   = PFD_MAIN_PLANE;
    descr.cColorBits   = 32;
    descr.cColorBits   = 24;
    descr.cStencilBits = 8;

    int  format_array[16] = {0};
    Uint format_count     = 0;

    BOOL status = wglChoosePixelFormatARB(device, attribs_pixel,
        NULL, 1, format_array, (UINT*) &format_count);

    if (status != 0 && format_count > 0) {
        pMemorySet(&descr, sizeof descr, 0x00);

        DescribePixelFormat(device, format_array[0],
            sizeof descr, &descr);

        SetPixelFormat(device, format_array[0], &descr);
    }
    else {
        int format = ChoosePixelFormat(device, &descr);

        if (format == 0) return NULL;

        if (SetPixelFormat(device, format, &descr) == 0)
            return NULL;
    }

    HGLRC context = wglCreateContextAttribsARB(device, 0, attribs_context);

    if (context == NULL) return NULL;

    if (wglMakeCurrent(device, context) != 0) return context;

    wglDeleteContext(context);

    return NULL;
}

B32 pWin32WindowOpenglCreate(PWin32Window* self, POpenglContextAttribs attribs)
{
    if (pWin32WindowOpenglStart() == 0) return 0;

    if (self->opengl == NULL) {
        self->opengl = pWin32OpenglCreate(self->device, attribs);

        if (self->opengl != NULL) return 1;
    }

    return 0;
}

void pWin32WindowOpenglDestroy(PWin32Window* self)
{
    if (self->opengl != NULL)
        wglDeleteContext(self->opengl);

    self->opengl = NULL;

    pWin32WindowOpenglStop();
}

B32 pWin32WindowOpenglEnable(PWin32Window* self, B32 state)
{
    return 0;
}

#endif
