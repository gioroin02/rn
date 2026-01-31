#ifndef RHO_SYSTEM_WINDOW_WIN32_COMMON_C
#define RHO_SYSTEM_WINDOW_WIN32_COMMON_C

#include "common.h"

extern RInt rho_win32_winproc_regular(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam);

static volatile LONG rho_win32_winclass_count = 0;

static RBool32 __rho_win32_window_start__()
{
    WNDCLASSEXW window_class = {0};

    window_class.cbSize        = sizeof window_class;
    window_class.style         = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc   = rho_win32_winproc_regular;
    window_class.hInstance     = GetModuleHandle(NULL);
    window_class.lpszClassName = L"RWindowRegular";
    window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);

    if (RegisterClassExW(&window_class) == 0) return 0;

    return 1;
}

static void __rho_win32_window_stop__()
{
    UnregisterClassW(L"RWindowRegular", GetModuleHandle(NULL));
}

RBool32 rho_win32_window_start()
{
    if (InterlockedIncrement(&rho_win32_winclass_count) == 1)
        return __rho_win32_window_start__();

    return 1;
}

void rho_win32_window_stop()
{
    if (InterlockedDecrement(&rho_win32_winclass_count) == 0)
        __rho_win32_window_stop__();
}

#endif
