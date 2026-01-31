#ifndef RHO_SYSTEM_WINDOW_OPENGL_WIN32_COMMON_C
#define RHO_SYSTEM_WINDOW_OPENGL_WIN32_COMMON_C

#include "common.h"

static volatile LONG rho_win32_opengl_count = 0;

WglCreateContextAttribsARB wglCreateContextAttribsARB = (WglCreateContextAttribsARB) NULL;
WglChoosePixelFormatARB    wglChoosePixelFormatARB    = (WglChoosePixelFormatARB)    NULL;

static RBool32 __rho_win32_window_opengl_start__()
{
    HWND window = CreateWindowW(L"RWindowRegular", L"RWindowDummy",
        0, 0, 0, 0, 0, NULL, NULL, NULL, NULL);

    if (window == NULL) return 0;

    PIXELFORMATDESCRIPTOR descr = {0};

    descr.nSize      = sizeof descr;
    descr.nVersion   = 1;
    descr.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    descr.iPixelType = PFD_TYPE_RGBA;
    descr.iLayerType = PFD_MAIN_PLANE;
    descr.cColorBits = 24;
    descr.cColorBits = 24;

    HDC   device = GetDC(window);
    int   format = ChoosePixelFormat(device, &descr);
    HGLRC dummy  = NULL;

    if (format != 0 && SetPixelFormat(device, format, &descr) != 0) {
        HGLRC context = wglCreateContext(device);

        if (wglMakeCurrent(device, context) == 0)
            wglDeleteContext(context);
        else
            dummy = context;
    }

    if (dummy != NULL) {
        wglCreateContextAttribsARB = (WglCreateContextAttribsARB)
            wglGetProcAddress("wglCreateContextAttribsARB");

        wglChoosePixelFormatARB = (WglChoosePixelFormatARB)
            wglGetProcAddress("wglChoosePixelFormatARB");

        wglDeleteContext(dummy);
    }

    DestroyWindow(window);

    if (wglCreateContextAttribsARB != NULL && wglChoosePixelFormatARB != NULL)
        return 1;

    return 0;
}

static void __rho_win32_window_opengl_stop__()
{
    wglChoosePixelFormatARB    = NULL;
    wglCreateContextAttribsARB = NULL;
}

RBool32 rho_win32_window_opengl_start()
{
    if (InterlockedIncrement(&rho_win32_opengl_count) == 1)
        return __rho_win32_window_opengl_start__();

    return 1;
}

void rho_win32_window_opengl_stop()
{
    if (InterlockedDecrement(&rho_win32_opengl_count) == 0)
        __rho_win32_window_opengl_stop__();
}

#endif
