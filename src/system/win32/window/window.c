#ifndef PX_WIN32_WINDOW_WINDOW_C
#define PX_WIN32_WINDOW_WINDOW_C

#include "window.h"

static RECT pxWin32Rect(ssize x, ssize y, ssize w, ssize h)
{
    RECT result;

    pxMemorySet(&result, sizeof result, 0xAB);

    result.left   = x;
    result.top    = y;
    result.right  = x + w;
    result.bottom = y + h;

    return result;
}

static PxStr16 pxWin32Str8ToStr16(u16* pntr, ssize size, PxStr8 string)
{
    PxStr16 result = pxStr16Make(PX_NULL, 0);

     size = MultiByteToWideChar(CP_UTF8, 0,
        (char*) string.values, string.size, (LPWSTR) pntr, size);

     if (size > 0) result = pxStr16Make(pntr, size);

     return result;
}

ssize CALLBACK pxWin32WindowProc(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam)
{
    PxWin32Window* self = (PxWin32Window*) GetWindowLongPtr(handle, GWLP_USERDATA);

    if (self == PX_NULL) return DefWindowProcW(handle, kind, wparam, lparam);

    switch (kind) {
        case WM_CLOSE:
        case WM_DESTROY:
            PostQuitMessage(0);
        return 0;

        default: break;
    }

    return DefWindowProcW(handle, kind, wparam, lparam);
}

PxWin32Window* pxWin32WindowReserve(PxMemoryArena* arena)
{
    return pxMemoryArenaReserveOneOf(arena, PxWin32Window);
}

b32
pxWin32WindowCreate(PxWin32Window* self, PxStr8 title, ssize width, ssize height)
{
    static u16 buffer[PX_SSIZE_KIBI];

    if (width <= 0 || height <= 0 || width > PX_SSIZE_MAX / height)
        return 0;

    PxStr16 string = pxWin32Str8ToStr16(buffer, sizeof buffer, title);

    if (string.size <= 0 || pxWin32WindowStart() == 0) return 0;

    HINSTANCE instance    = GetModuleHandle(PX_NULL);
    RECT      window_rect = pxWin32Rect(0, 0, width, height);

    AdjustWindowRect(&window_rect, 0, 0);

    HWND handle = CreateWindowExW(0, (LPWSTR) PX_WIN32_CLASS_NAME.values,
        string.values, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        window_rect.right, window_rect.bottom, PX_NULL, PX_NULL, instance, PX_NULL);

    if (handle != PX_NULL) {
        self->handle   = handle;
        self->instance = instance;

        SetWindowLongPtr(self->handle, GWLP_USERDATA,
            (LONG_PTR) self);

        return 1;
    }

    pxWin32WindowStop();

    return 0;
}

void pxWin32WindowDestroy(PxWin32Window* self)
{
    if (self->handle != PX_NULL)
        DestroyWindow(self->handle);

    pxMemorySet(self, sizeof *self, 0xAB);

    pxWin32WindowStop();
}

b32 pxWin32WindowVisibilitySet(PxWin32Window* self, PxWindowVisibility visibility)
{
    switch (visibility) {
        case PxWindowVisibility_Hide: ShowWindow(self->handle, SW_HIDE); break;
        case PxWindowVisibility_Show: ShowWindow(self->handle, SW_SHOW); break;

        default: return 0;
    }

    return 1;
}

#endif // PX_WI32_WINDOW_WINDOW_C
