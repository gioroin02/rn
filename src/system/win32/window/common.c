#ifndef PX_WIN32_WINDOW_COMMON_C
#define PX_WIN32_WINDOW_COMMON_C

#include "common.h"

static volatile LONG px_win32_winclass_count = 0;

b32 pxWin32WindowStart()
{
    if (InterlockedIncrement(&px_win32_winclass_count) == 1)
        return pxWin32WindowStartImpl();

    return 1;
}

b32 pxWin32WindowStartImpl()
{
    HINSTANCE instance   = GetModuleHandle(PX_NULL);
    LPWSTR    class_name = (LPWSTR) PX_WIN32_CLASS_NAME.values;

    WNDCLASSW window_class;

    pxMemorySet(&window_class, sizeof window_class, 0x00);

    window_class.style         = CS_HREDRAW | CS_VREDRAW,
    window_class.lpfnWndProc   = pxWin32WindowProc;
    window_class.hInstance     = instance;
    window_class.lpszClassName = class_name;

    if (RegisterClassW(&window_class) == 0) return 0;

    return 1;
}

void pxWin32WindowStop()
{
    if (InterlockedDecrement(&px_win32_winclass_count) == 0)
        pxWin32WindowStopImpl();
}

void pxWin32WindowStopImpl()
{
    HINSTANCE instance   = GetModuleHandle(PX_NULL);
    LPWSTR    class_name = (LPWSTR) PX_WIN32_CLASS_NAME.values;

    UnregisterClassW(class_name, instance);
}

#endif // PX_WIN32_WINDOW_COMMON_C
