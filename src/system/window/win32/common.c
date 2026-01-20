#ifndef P_SYSTEM_WIN32_WINDOW_COMMON_C
#define P_SYSTEM_WIN32_WINDOW_COMMON_C

#include "common.h"

extern Int pWin32WindowProcRegular(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam);

static volatile LONG p_win32_winclass_count = 0;

Bool pWin32WindowStart()
{
    if (InterlockedIncrement(&p_win32_winclass_count) == 1)
        return pWin32WindowStartImpl();

    return 1;
}

Bool pWin32WindowStartImpl()
{
    WNDCLASSEXW window_class;

    pMemorySet(&window_class, sizeof window_class, 0x00);

    window_class.cbSize        = sizeof window_class;
    window_class.style         = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc   = pWin32WindowProcRegular;
    window_class.hInstance     = GetModuleHandle(NULL);
    window_class.lpszClassName = L"PWindowRegular";
    window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);

    if (RegisterClassExW(&window_class) == 0) return 0;

    HWND window = CreateWindowW(L"PWindowRegular", L"WindowDummy",
        0, 0, 0, 0, 0, NULL, NULL, NULL, NULL);

    if (window == NULL) return 0;

    PIXELFORMATDESCRIPTOR descr;

    pMemorySet(&descr, sizeof descr, 0x00);

    descr.nSize      = sizeof descr;
    descr.nVersion   = 1;
    descr.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    descr.iPixelType = PFD_TYPE_RGBA;
    descr.iLayerType = PFD_MAIN_PLANE;
    descr.cColorBits = 24;
    descr.cColorBits = 24;

    HDC device = GetDC(window);
    int format = ChoosePixelFormat(device, &descr);

    HGLRC dummy = NULL;

    if (format != 0 && SetPixelFormat(device, format, &descr) != 0) {
        HGLRC context = wglCreateContext(device);

        if (wglMakeCurrent(device, context) == 0)
            wglDeleteContext(context);
        else
            dummy = context;
    }

    if (dummy != NULL) {
        wglCreateContextAttribsARB = (LPFN_wglCreateContextAttribsARB)
            wglGetProcAddress("wglCreateContextAttribsARB");

        wglChoosePixelFormatARB = (LPFN_wglChoosePixelFormatARB)
            wglGetProcAddress("wglChoosePixelFormatARB");

        wglDeleteContext(dummy);
    }

    DestroyWindow(window);

    if (wglCreateContextAttribsARB != NULL && wglChoosePixelFormatARB != NULL)
        return 1;

    pWin32WindowStopImpl();

    return 0;
}

void pWin32WindowStop()
{
    if (InterlockedDecrement(&p_win32_winclass_count) == 0)
        pWin32WindowStopImpl();
}

void pWin32WindowStopImpl()
{
    wglChoosePixelFormatARB    = NULL;
    wglCreateContextAttribsARB = NULL;

    UnregisterClassW(L"PWindowRegular", GetModuleHandle(NULL));
}

POINT pWin32Point(Int x, Int y)
{
    POINT result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.x = x;
    result.y = y;

    return result;
}

POINT pWin32CursorPoint(HWND handle)
{
    POINT result;

    pMemorySet(&result, sizeof result, 0xAB);

    GetCursorPos(&result);

    return result;
}

RECT pWin32Rect(Int x, Int y, Int w, Int h)
{
    RECT result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.left   = x;
    result.top    = y;
    result.right  = x + w;
    result.bottom = y + h;

    return result;
}

RECT pWin32RectAdjusted(Int x, Int y, Int w, Int h)
{
    RECT result;

    pMemorySet(&result, sizeof result, 0xAB);

    result.left   = x;
    result.top    = y;
    result.right  = x + w;
    result.bottom = y + h;

    AdjustWindowRect(&result, 0, 0);

    return result;
}

RECT pWin32WindowRect(HWND handle)
{
    RECT result;

    pMemorySet(&result, sizeof result, 0xAB);

    GetWindowRect(handle, &result);

    return result;
}

RECT pWin32ClientRect(HWND handle)
{
    RECT result;

    pMemorySet(&result, sizeof result, 0xAB);

    GetClientRect(handle, &result);

    return result;
}

PString16 pWin32Str8ToStr16(U16* pntr, Int size, PString8 string)
{
    PString16 result = pString16Make(NULL, 0);

     size = MultiByteToWideChar(CP_UTF8, 0,
        (char*) string.values, string.size, (LPWSTR) pntr, size);

     if (size > 0) result = pString16Make(pntr, size);

     return result;
}

#endif // P_SYSTEM_WIN32_WINDOW_COMMON_C
