#ifndef RHO_SYSTEM_WINDOW_WIN32_WINDOW_C
#define RHO_SYSTEM_WINDOW_WIN32_WINDOW_C

#include "window.h"

#define RHO_WIN32_WINDOW_TIMER_PAINT ((RInt) 1)

static RString16 rho_win32_utf8_to_utf16(RString8 string, RChar16* buffer, RInt size)
{
    size = MultiByteToWideChar(CP_UTF8, 0,
        (RChar8*) string.values, string.size, (LPWSTR) buffer, size);

    return rho_string16_make(buffer, size);
}

static POINT rho_win32_window_rect(RInt width, RInt height)
{
    POINT result = {0};
    RECT  rect   = {0};

    rho_memory_set(&rect, sizeof rect, 0xAB);

    rect.left   = 0;
    rect.top    = 0;
    rect.right  = width;
    rect.bottom = height;

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

    result.x = rect.right - rect.left;
    result.y = rect.bottom - rect.top;

    return result;
}

static void rho_win32_window_callback(RWin32Window* self, RWindowEvent event)
{
    if (self->proc != NULL)
        ((RWindowCallback*) self->proc)(self->ctxt, event);
}

RInt rho_win32_winproc_regular(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam)
{
    RWin32Window* self = (RWin32Window*) GetWindowLongPtr(handle, GWLP_USERDATA);

    if (self == NULL) return DefWindowProcW(handle, kind, wparam, lparam);

    RInt result = 0;

    switch (kind) {
        case WM_ENTERSIZEMOVE:
            SetTimer(self->handle, RHO_WIN32_WINDOW_TIMER_PAINT, 20, NULL);
        break;

        case WM_EXITSIZEMOVE:
            KillTimer(self->handle, RHO_WIN32_WINDOW_TIMER_PAINT);
        break;

        case WM_CLOSE: PostQuitMessage(0); break;

        case WM_TIMER: {
            if (wparam == RHO_WIN32_WINDOW_TIMER_PAINT)
                InvalidateRect(self->handle, NULL, 1);
        } break;

        case WM_ERASEBKGND: result = 1; break;

        case WM_PAINT: {
            RWindowEvent event = rho_window_event_paint(self->handle);
            PAINTSTRUCT  paint = {0};

            HDC device = BeginPaint(self->handle, &paint);

            rho_win32_window_callback(self, event);

            EndPaint(self->handle, &paint);
        } break;

        case WM_GETMINMAXINFO: {
            MINMAXINFO* info = (MINMAXINFO*) lparam;

            POINT min = rho_win32_window_rect(
                self->attribs.width_min, self->attribs.height_min);

            POINT max = rho_win32_window_rect(
                self->attribs.width_max, self->attribs.height_max);

            info->ptMinTrackSize.x = min.x;
            info->ptMaxTrackSize.x = max.x;
            info->ptMinTrackSize.y = min.y;
            info->ptMaxTrackSize.y = max.y;
        } break;

        default: result = -1;
    }

    if (result < 0) return DefWindowProcW(handle, kind, wparam, lparam);

    return result;
}

RWin32Window* rho_win32_window_reserve(RMemoryArena* arena)
{
    return rho_memory_arena_reserve_of(arena, RWin32Window, 1);
}

RBool32 rho_win32_window_create(RWin32Window* self, RString8 title, RInt width, RInt height)
{
    static RChar16 buffer[4 * RHO_MEMORY_KIB] = {0};

    rho_memory_set(self, sizeof *self, 0xAB);

    self->handle  = NULL;
    self->device  = NULL;
    self->opengl  = NULL;
    self->ctxt    = NULL;
    self->proc    = NULL;
    self->attribs = rho_window_attribs_make();

    if (width <= 0 || height <= 0 || width > RHO_INT_MAX / height) return 0;

    RString16 title16 = rho_win32_utf8_to_utf16(title, buffer, sizeof buffer);
    RInt      style   = WS_OVERLAPPEDWINDOW;

    if (title16.size <= 0 || rho_win32_window_start() == 0) return 0;

    POINT area = rho_win32_window_rect(width, height);

    HWND handle = CreateWindowW(L"RWindowRegular", (RUint16*) title16.values,
        style, 100, 100, area.x, area.y, NULL, NULL, NULL, NULL);

    if (handle != NULL) {
        self->handle = handle;
        self->device = GetDC(handle);

        self->attribs.visibility = RWindowVisibility_None;
        self->attribs.coord_x    = 100;
        self->attribs.coord_y    = 100;
        self->attribs.width      = width;
        self->attribs.width_max  = 1920;
        self->attribs.width_min  = 400;
        self->attribs.height     = height;
        self->attribs.height_max = 1080;
        self->attribs.height_min = 300;

        SetWindowLongPtr(self->handle, GWLP_USERDATA, (LONG_PTR) self);

        InvalidateRect(self->handle, NULL, 1);

        return 1;
    }

    rho_win32_window_stop();

    return 0;
}

void rho_win32_window_destroy(RWin32Window* self)
{
    if (self->opengl != NULL) wglDeleteContext(self->opengl);
    if (self->handle != NULL) DestroyWindow(self->handle);

    rho_memory_set(self, sizeof *self, 0xAB);

    rho_win32_window_stop();
}

RBool32 rho_win32_window_poll_events(RWin32Window* self)
{
    MSG message = {0};

    RWindowEvent temp = rho_window_event_none();

    while (PeekMessageW(&message, 0, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);

        switch (message.message) {
            case WM_QUIT: temp = rho_window_event_quit((RWindow*) self); break;

            case WM_KEYDOWN: {
                RWindowKeyboardKey key  = rho_win32_window_convert_key(message.wParam);
                RInt               scan = (message.lParam >> 16) & 0xff;

                temp = rho_window_event_keyboard_key((RWindow*) self, key, 1, scan);
            } break;

            case WM_KEYUP: {
                RWindowKeyboardKey key  = rho_win32_window_convert_key(message.wParam);
                RInt               scan = (message.lParam >> 16) & 0xff;

                temp = rho_window_event_keyboard_key((RWindow*) self, key, 0, scan);
            } break;

            default: break;
        }

        if (temp.kind != RWindowEvent_None)
            rho_win32_window_callback(self, temp);
    }

    return 1;
}

void rho_win32_window_swap_buffers(RWin32Window* self)
{
    SwapBuffers(self->device);
}

RBool32 rho_win32_window_set_attribs(RWin32Window* self, RWindowAttribs attribs)
{
    POINT area = rho_win32_window_rect(attribs.width, attribs.height);

    SetWindowPos(self->handle, NULL, 0, 0, area.x, area.y,
        SWP_NOZORDER | SWP_NOOWNERZORDER);

    switch (attribs.visibility) {
        case RWindowVisibility_Hide: ShowWindow(self->handle, SW_HIDE); break;
        case RWindowVisibility_Show: ShowWindow(self->handle, SW_SHOW); break;

        default: break;
    }

    self->attribs = attribs;

    return 1;
}

RWindowAttribs rho_win32_window_get_attribs(RWin32Window* self)
{
    RECT rect = {0};

    GetClientRect(self->handle, &rect);

    self->attribs.coord_x = rect.left;
    self->attribs.coord_y = rect.top;
    self->attribs.width   = rect.right - rect.left;
    self->attribs.height  = rect.bottom - rect.top;

    RUint32 visibility = 0;

    visibility = IsWindowVisible(self->handle) != 0 ? 1 << 0 : 0;

    switch (visibility) {
        case 0:      self->attribs.visibility = RWindowVisibility_Show; break;
        case 1 << 0: self->attribs.visibility = RWindowVisibility_Hide; break;

        default: break;
    }

    return self->attribs;
}

RBool32 rho_win32_window_set_callback(RWin32Window* self, void* ctxt, void* proc)
{
    self->ctxt = ctxt;
    self->proc = proc;

    return 1;
}

void* rho_win32_window_get_callback(RWin32Window* self)
{
    return self->proc;
}

#endif
