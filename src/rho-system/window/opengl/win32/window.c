#ifndef RHO_SYSTEM_WINDOW_OPENGL_WIN32_WINDOW_C
#define RHO_SYSTEM_WINDOW_OPENGL_WIN32_WINDOW_C

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

static int rho_win32_opengl_profile(ROpenglProfile profile)
{
    switch (profile) {
        case ROpenglProfile_Compatibility:
            return WGL_CONTEXT_PROFILE_COMPATIBILITY_ARB;

        case ROpenglProfile_Core:
            return WGL_CONTEXT_PROFILE_CORE_ARB;

        default: break;
    }

    return 0;
}

static int rho_win32_opengl_flag(ROpenglContextFlag flag)
{
    int result = 0;

    if ((flag & ROpenglContextFlag_Debug) != 0)
        result |= WGL_CONTEXT_DEBUG_BIT_ARB;

    return result;
}

static HGLRC rho_win32_opengl_create(HDC device, ROpenglContextAttribs attribs)
{
    int attribs_context[32] = {0};
    int attribs_pixel[32]   = {0};

    int config_context[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, attribs.version_major,
        WGL_CONTEXT_MINOR_VERSION_ARB, attribs.version_minor,
        WGL_CONTEXT_PROFILE_MASK_ARB,  rho_win32_opengl_profile(attribs.profile),
        WGL_CONTEXT_FLAGS_ARB,         rho_win32_opengl_flag(attribs.flag),
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

    rho_memory_copy(attribs_context, sizeof config_context, config_context);
    rho_memory_copy(attribs_pixel,     sizeof config_pixel,   config_pixel);

    PIXELFORMATDESCRIPTOR descr = {0};

    rho_memory_set(&descr, sizeof descr, 0x00);

    descr.nSize        = sizeof descr;
    descr.nVersion     = 1;
    descr.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    descr.iPixelType   = PFD_TYPE_RGBA;
    descr.iLayerType   = PFD_MAIN_PLANE;
    descr.cColorBits   = 32;
    descr.cColorBits   = 24;
    descr.cStencilBits = 8;

    int  format_array[16] = {0};
    RInt format_count     = 0;

    BOOL status = wglChoosePixelFormatARB(device, attribs_pixel,
        NULL, 1, format_array, (UINT*) &format_count);

    if (status != 0 && format_count > 0) {
        rho_memory_set(&descr, sizeof descr, 0x00);

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

RBool32 rho_win32_window_opengl_create(RWin32Window* self, ROpenglContextAttribs attribs)
{
    if (rho_win32_window_opengl_start() == 0) return 0;

    if (self->opengl == NULL) {
        self->opengl = rho_win32_opengl_create(self->device, attribs);

        if (self->opengl != NULL) return 1;
    }

    return 0;
}

void rho_win32_window_opengl_destroy(RWin32Window* self)
{
    if (self->opengl != NULL)
        wglDeleteContext(self->opengl);

    self->opengl = NULL;

    rho_win32_window_opengl_stop();
}

RBool32 rho_win32_window_opengl_enable(RWin32Window* self, RBool32 state)
{
    return 0;
}

#endif
