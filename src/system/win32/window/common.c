#ifndef PX_WIN32_WINDOW_COMMON_C
#define PX_WIN32_WINDOW_COMMON_C

#include "common.h"

extern ssize pxWin32WindowProc(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam);

static volatile LONG px_win32_winclass_count = 0;

b32 pxWin32WindowStart()
{
    if (InterlockedIncrement(&px_win32_winclass_count) == 1)
        return pxWin32WindowStartImpl();

    return 1;
}

b32 pxWin32WindowStartImpl()
{
    WNDCLASSEXW window_class;

    pxMemorySet(&window_class, sizeof window_class, 0x00);

    window_class.cbSize        = sizeof window_class;
    window_class.style         = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc   = pxWin32WindowProc;
    window_class.hInstance     = GetModuleHandle(PX_NULL);
    window_class.lpszClassName = L"PxWindowRegular";
    window_class.hCursor       = LoadCursor(PX_NULL, IDC_ARROW);

    if (RegisterClassExW(&window_class) == 0) return 0;

    return 1;
}

void pxWin32WindowStop()
{
    if (InterlockedDecrement(&px_win32_winclass_count) == 0)
        pxWin32WindowStopImpl();
}

void pxWin32WindowStopImpl()
{
    UnregisterClassW(L"PxWindowRegular", GetModuleHandle(PX_NULL));
}

#endif // PX_WIN32_WINDOW_COMMON_C
