#ifndef P_SYSTEM_WIN32_WINDOW_WINDOW_C
#define P_SYSTEM_WIN32_WINDOW_WINDOW_C

#include "window.h"

#define P_SYSTEM_WIN32_TIMER_PAINT ((Int) PWindowTimer_Paint)

static RECT pWin32AdjustWindowRect(Int left, Int top, Int right, Int bottom)
{
    RECT result;

    result.left   = left;
    result.top    = top + 40;
    result.right  = right;
    result.bottom = bottom;

    return result;
}

Int pWin32WindowProcRegular(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam)
{
    PWin32Window* self = (PWin32Window*) GetWindowLongPtr(handle, GWLP_USERDATA);

    if (self == NULL) return DefWindowProcW(handle, kind, wparam, lparam);

    Int result = 0;

    switch (kind) {
        case WM_ENTERSIZEMOVE:
            SetTimer(handle, P_SYSTEM_WIN32_TIMER_PAINT, 20, NULL);
        break;

        case WM_EXITSIZEMOVE:
            KillTimer(handle, P_SYSTEM_WIN32_TIMER_PAINT);
        break;

        case WM_TIMER: {
            if (wparam == P_SYSTEM_WIN32_TIMER_PAINT)
                InvalidateRect(self->handle, NULL, 1);
        } break;

        case WM_GETMINMAXINFO: {
            MINMAXINFO* info = (MINMAXINFO*) lparam;

            info->ptMinTrackSize.x = self->attribs.width_min;
            info->ptMaxTrackSize.x = self->attribs.width_max;
            info->ptMinTrackSize.y = self->attribs.height_min;
            info->ptMaxTrackSize.y = self->attribs.height_max;
        } break;

        case WM_ERASEBKGND: result = 1; break;

        case WM_PAINT: {
            PAINTSTRUCT paint;

            HDC device = BeginPaint(self->handle, &paint);

            if (self->timer_proc != NULL) {
                ((PWindowTimerCallback*) self->timer_proc)(
                    self->timer_ctxt, (PWindow*) self, PWindowTimer_Paint);
            }

            EndPaint(self->handle, &paint);
        } break;

        case WM_CLOSE: PostQuitMessage(0); break;

        default: result = -1;
    }

    if (result < 0) return DefWindowProcW(handle, kind, wparam, lparam);

    return result;
}

PWin32Window* pWin32WindowReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32Window);
}

Bool pWin32WindowCreate(PWin32Window* self, PString8 title, Int width, Int height)
{
    static U16 buffer[P_MEMORY_KIB];

    if (width <= 0 || height <= 0 || width > P_INT_MAX / height) return 0;

    RECT      rect   = pWin32AdjustWindowRect(0, 0, width, height);
    PString16 string = pWin32Str8ToStr16(buffer, sizeof buffer, title);

    if (string.size <= 0 || pWin32WindowStart() == 0) return 0;

    Int style = WS_OVERLAPPEDWINDOW;
    Int x     = 100;
    Int y     = 100;

    width  = rect.right - rect.left;
    height = rect.bottom - rect.top;

    HWND handle = CreateWindowW(L"PWindowRegular", string.values,
        style, x, y, width, height, NULL, NULL, NULL, NULL);

    if (handle != NULL) {
        self->handle = handle;
        self->device = GetDC(handle);
        self->opengl = NULL;

        self->attribs.visibility = PWindowVisibility_None;
        self->attribs.coord_x    = x;
        self->attribs.coord_y    = y;
        self->attribs.width      = width;
        self->attribs.width_max  = 1920;
        self->attribs.width_min  = 400;
        self->attribs.height     = height;
        self->attribs.height_max = 1080;
        self->attribs.height_min = 300;
        self->timer_ctxt         = NULL;
        self->timer_proc         = NULL;

        SetWindowLongPtr(self->handle, GWLP_USERDATA, (LONG_PTR) self);

        InvalidateRect(self->handle, NULL, 1);

        return 1;
    }

    pWin32WindowStop();

    return 0;
}

void pWin32WindowDestroy(PWin32Window* self)
{
    if (self->handle != NULL) {
        DeleteDC(self->device);

        DestroyWindow(self->handle);
    }

    pMemorySet(self, sizeof *self, 0xAB);

    pWin32WindowStop();
}

Bool pWin32WindowPollEvent(PWin32Window* self, PWindowEvent* event)
{
    MSG message;

    while (PeekMessageW(&message, 0, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);

        switch (message.message) {
            case WM_QUIT: *event = pWindowEventQuit((PWindow*) self); return 1;

            case WM_CREATE:  *event = pWindowEventWindowCreate((PWindow*) self);  return 1;
            case WM_DESTROY: *event = pWindowEventWindowDestroy((PWindow*) self); return 1;

            case WM_KEYDOWN: {
                PWindowKeybdKey key  = pWin32WindowConvertKey(message.wParam);
                Int             scan = (message.lParam >> 16) & 0xff;

                *event = pWindowEventKeybdKey((PWindow*) self, key, 1, scan);
            } return 1;

            case WM_KEYUP: {
                PWindowKeybdKey key  = pWin32WindowConvertKey(message.wParam);
                Int             scan = (message.lParam >> 16) & 0xff;

                *event = pWindowEventKeybdKey((PWindow*) self, key, 0, scan);
            } return 1;

            default: break;
        }
    }

    return 0;
}

void pWin32WindowSwapBuffers(PWin32Window* self)
{
    SwapBuffers(self->device);
}

Bool pWin32WindowSetAttribs(PWin32Window* self, PWindowAttribs attribs)
{
    self->attribs = attribs;

    WINDOWPLACEMENT placement;

    placement.length                  = sizeof placement;
    placement.rcNormalPosition.left   = attribs.coord_x;
    placement.rcNormalPosition.top    = attribs.coord_y;
    placement.rcNormalPosition.right  = attribs.coord_x + attribs.width;
    placement.rcNormalPosition.bottom = attribs.coord_y + attribs.height;

    switch (attribs.visibility) {
        case PWindowVisibility_Hide: placement.showCmd = SW_HIDE; break;
        case PWindowVisibility_Show: placement.showCmd = SW_SHOW; break;

        default: break;
    }

    SetWindowPlacement(self->handle, &placement);

    return 1;
}

PWindowAttribs pWin32WindowGetAttribs(PWin32Window* self)
{
    WINDOWPLACEMENT placement;
    RECT            rect;

    GetWindowPlacement(self->handle, &placement);
    GetWindowRect(self->handle, &rect);

    self->attribs.coord_x = rect.left;
    self->attribs.coord_y = rect.top;
    self->attribs.width   = rect.right - rect.left;
    self->attribs.height  = rect.bottom - rect.top;

    switch (placement.showCmd) {
        case SW_HIDE: self->attribs.visibility = PWindowVisibility_Hide; break;
        case SW_SHOW: self->attribs.visibility = PWindowVisibility_Show; break;

        default: break;
    }

    return self->attribs;
}

Bool pWin32WindowSetTimerCallback(PWin32Window* self, void* ctxt, void* proc)
{
    self->timer_ctxt = ctxt;
    self->timer_proc = proc;

    return 1;
}

void* pWin32WindowGetTimerCallback(PWin32Window* self)
{
    return self->timer_proc;
}

#endif
