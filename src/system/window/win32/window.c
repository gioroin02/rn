#ifndef P_SYSTEM_WIN32_WINDOW_WINDOW_C
#define P_SYSTEM_WIN32_WINDOW_WINDOW_C

#include "window.h"

#define P_SYSTEM_WIN32_TIMER_RESIZE ((Int) 1)

static PWindowKeyboardKey pWin32WindowConvertKey(WORD key_code)
{
    switch (key_code) {
        case 'A':            return PWindowKeyboardKey_A;            break;
        case 'B':            return PWindowKeyboardKey_B;            break;
        case 'C':            return PWindowKeyboardKey_C;            break;
        case 'D':            return PWindowKeyboardKey_D;            break;
        case 'E':            return PWindowKeyboardKey_E;            break;
        case 'F':            return PWindowKeyboardKey_F;            break;
        case 'G':            return PWindowKeyboardKey_G;            break;
        case 'H':            return PWindowKeyboardKey_H;            break;
        case 'I':            return PWindowKeyboardKey_I;            break;
        case 'J':            return PWindowKeyboardKey_J;            break;
        case 'K':            return PWindowKeyboardKey_K;            break;
        case 'L':            return PWindowKeyboardKey_L;            break;
        case 'M':            return PWindowKeyboardKey_M;            break;
        case 'N':            return PWindowKeyboardKey_N;            break;
        case 'O':            return PWindowKeyboardKey_O;            break;
        case 'P':            return PWindowKeyboardKey_P;            break;
        case 'Q':            return PWindowKeyboardKey_Q;            break;
        case 'R':            return PWindowKeyboardKey_R;            break;
        case 'S':            return PWindowKeyboardKey_S;            break;
        case 'T':            return PWindowKeyboardKey_T;            break;
        case 'U':            return PWindowKeyboardKey_U;            break;
        case 'V':            return PWindowKeyboardKey_V;            break;
        case 'W':            return PWindowKeyboardKey_W;            break;
        case 'X':            return PWindowKeyboardKey_X;            break;
        case 'Y':            return PWindowKeyboardKey_Y;            break;
        case 'Z':            return PWindowKeyboardKey_Z;            break;
        case '0':            return PWindowKeyboardKey_0;            break;
        case '1':            return PWindowKeyboardKey_1;            break;
        case '2':            return PWindowKeyboardKey_2;            break;
        case '3':            return PWindowKeyboardKey_3;            break;
        case '4':            return PWindowKeyboardKey_4;            break;
        case '5':            return PWindowKeyboardKey_5;            break;
        case '6':            return PWindowKeyboardKey_6;            break;
        case '7':            return PWindowKeyboardKey_7;            break;
        case '8':            return PWindowKeyboardKey_8;            break;
        case '9':            return PWindowKeyboardKey_9;            break;
        case VK_SPACE:       return PWindowKeyboardKey_Space;        break;
        case VK_OEM_MINUS:   return PWindowKeyboardKey_Minus;        break;
        case VK_OEM_PLUS:    return PWindowKeyboardKey_Equal;        break;
        case VK_OEM_4:       return PWindowKeyboardKey_SquareLeft;   break;
        case VK_OEM_6:       return PWindowKeyboardKey_SquareRight;  break;
        case VK_OEM_5:       return PWindowKeyboardKey_BackSlash;    break;
        case VK_OEM_1:       return PWindowKeyboardKey_SemiColon;    break;
        case VK_OEM_7:       return PWindowKeyboardKey_Apostrophe;   break;
        case VK_OEM_3:       return PWindowKeyboardKey_Grave;        break;
        case VK_OEM_COMMA:   return PWindowKeyboardKey_Comma;        break;
        case VK_OEM_PERIOD:  return PWindowKeyboardKey_Period;       break;
        case VK_OEM_2:       return PWindowKeyboardKey_Slash;        break;
        case VK_UP:          return PWindowKeyboardKey_Up;           break;
        case VK_DOWN:        return PWindowKeyboardKey_Down;         break;
        case VK_LEFT:        return PWindowKeyboardKey_Left;         break;
        case VK_RIGHT:       return PWindowKeyboardKey_Right;        break;
        case VK_HOME:        return PWindowKeyboardKey_Home;         break;
        case VK_END:         return PWindowKeyboardKey_End;          break;
        case VK_PRIOR:       return PWindowKeyboardKey_PageUp;       break;
        case VK_NEXT:        return PWindowKeyboardKey_PageDown;     break;
        case VK_INSERT:      return PWindowKeyboardKey_Insert;       break;
        case VK_DELETE:      return PWindowKeyboardKey_Delete;       break;
        case VK_F1:          return PWindowKeyboardKey_F1;           break;
        case VK_F2:          return PWindowKeyboardKey_F2;           break;
        case VK_F3:          return PWindowKeyboardKey_F3;           break;
        case VK_F4:          return PWindowKeyboardKey_F4;           break;
        case VK_F5:          return PWindowKeyboardKey_F5;           break;
        case VK_F6:          return PWindowKeyboardKey_F6;           break;
        case VK_F7:          return PWindowKeyboardKey_F7;           break;
        case VK_F8:          return PWindowKeyboardKey_F8;           break;
        case VK_F9:          return PWindowKeyboardKey_F9;           break;
        case VK_F10:         return PWindowKeyboardKey_F10;          break;
        case VK_F11:         return PWindowKeyboardKey_F11;          break;
        case VK_F12:         return PWindowKeyboardKey_F12;          break;
        case VK_RETURN:      return PWindowKeyboardKey_Enter;        break;
        case VK_ESCAPE:      return PWindowKeyboardKey_Escape;       break;
        case VK_BACK:        return PWindowKeyboardKey_BackSpace;    break;
        case VK_TAB:         return PWindowKeyboardKey_Tab;          break;

        default: break;
    }

    return PWindowKeyboardKey_None;
}

#define WGL_TYPE_RGBA_ARB (1)

#define WGL_CONTEXT_DEBUG_BIT_ARB    (0x0001)
#define WGL_CONTEXT_PROFILE_CORE_ARB (0x0001)

#define WGL_DRAW_TO_WINDOW_ARB (0x2001)
#define WGL_SUPPORT_OPENGL_ARB (0x2010)
#define WGL_DOUBLE_BUFFER_ARB  (0x2011)
#define WGL_PIXEL_TYPE_ARB     (0x2013)
#define WGL_COLOR_BITS_ARB     (0x2014)
#define WGL_DEPTH_BITS_ARB     (0x2022)
#define WGL_STENCIL_BITS_ARB   (0x2023)
#define WGL_SAMPLE_BUFFERS_ARB (0x2041)
#define WGL_SAMPLES_ARB        (0x2042)

#define WGL_CONTEXT_MAJOR_VERSION_ARB (0x2091)
#define WGL_CONTEXT_MINOR_VERSION_ARB (0x2092)
#define WGL_CONTEXT_FLAGS_ARB         (0x2094)
#define WGL_CONTEXT_PROFILE_MASK_ARB  (0x9126)

static HGLRC pWin32CreateOpenGlContextCore33(PWin32Window* self)
{
    int attribs_pixel[] = {
        WGL_DRAW_TO_WINDOW_ARB, 1,
        WGL_SUPPORT_OPENGL_ARB, 1,
        WGL_DOUBLE_BUFFER_ARB,  1,
        WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,     24,
        WGL_DEPTH_BITS_ARB,     24,
        WGL_STENCIL_BITS_ARB,   8,
        0
    };

    int attribs_context[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_PROFILE_CORE_ARB,
        WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_DEBUG_BIT_ARB,
        0,
    };

    PIXELFORMATDESCRIPTOR descr;

    pMemorySet(&descr, sizeof descr, 0x00);

    descr.nSize      = sizeof descr;
    descr.nVersion   = 1;
    descr.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    descr.iPixelType = PFD_TYPE_RGBA;
    descr.iLayerType = PFD_MAIN_PLANE;
    descr.cColorBits = 24;
    descr.cColorBits = 24;

    int  format_array[16] = {0};
    Uint format_count     = 0;

    BOOL status = wglChoosePixelFormatARB(self->device,
        attribs_pixel, NULL, 1, format_array, (UINT*) &format_count);

    if (status != 0 && format_count > 0) {
        pMemorySet(&descr, sizeof descr, 0x00);

        DescribePixelFormat(self->device, format_array[0],
            sizeof descr, &descr);

        SetPixelFormat(self->device, format_array[0], &descr);
    }
    else {
        int format = ChoosePixelFormat(self->device, &descr);

        if (format == 0 || SetPixelFormat(self->device, format, &descr) == 0)
            return NULL;
    }

    HGLRC context = wglCreateContextAttribsARB(self->device, 0, attribs_context);

    if (context == NULL) return NULL;

    if (wglMakeCurrent(self->device, context) != 0)
        return context;

    wglDeleteContext(context);

    return NULL;
}

void* pWin32OpenglProcAddress(const char* name)
{
    HMODULE opengl = GetModuleHandle("opengl32.dll");
    void*   result = wglGetProcAddress(name);

    if (result != NULL) return result;

    return GetProcAddress(opengl, name);
}

Int pWin32WindowProcRegular(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam)
{
    PWin32Window* self = (PWin32Window*) GetWindowLongPtr(handle, GWLP_USERDATA);

    if (self == NULL) return DefWindowProcW(handle, kind, wparam, lparam);

    Int result = 0;

    switch (kind) {
        case WM_ENTERSIZEMOVE:
            SetTimer(handle, P_SYSTEM_WIN32_TIMER_RESIZE, 20, NULL);
        break;

        case WM_EXITSIZEMOVE:
            KillTimer(handle, P_SYSTEM_WIN32_TIMER_RESIZE);
        break;

        case WM_TIMER: {
            if (wparam == P_SYSTEM_WIN32_TIMER_RESIZE)
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

            if (self->paint_proc != NULL) {
                ((PWindowCallback*) self->paint_proc)(
                    self->paint_ctxt, (PWindow*) self);
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

    RECT      rect   = pWin32RectAdjusted(0, 0, width, height);
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
        self->opengl = pWin32CreateOpenGlContextCore33(self);

        self->attribs.visibility = PWindowVisibility_None;
        self->attribs.coord_x    = x;
        self->attribs.coord_y    = y;
        self->attribs.width      = width;
        self->attribs.width_max  = 1920;
        self->attribs.width_min  = 400;
        self->attribs.height     = height;
        self->attribs.height_max = 1080;
        self->attribs.height_min = 300;
        self->paint_ctxt         = NULL;
        self->paint_proc         = NULL;

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
                PWindowKeyboardKey key  = pWin32WindowConvertKey(message.wParam);
                Int               scan = (message.lParam >> 16) & 0xff;

                *event = pWindowEventKeyboardKey((PWindow*) self, key, 1, scan);
            } return 1;

            case WM_KEYUP: {
                PWindowKeyboardKey key  = pWin32WindowConvertKey(message.wParam);
                Int               scan = (message.lParam >> 16) & 0xff;

                *event = pWindowEventKeyboardKey((PWindow*) self, key, 0, scan);
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

    GetWindowPlacement(self->handle, &placement);

    RECT rect = pWin32WindowRect(self->handle);

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

Bool pWin32WindowSetCallback(PWin32Window* self, void* ctxt, void* proc)
{
    self->paint_ctxt = ctxt;
    self->paint_proc = proc;

    return 1;
}

void* pWin32WindowGetCallback(PWin32Window* self)
{
    return self->paint_proc;
}

#endif // P_WI32_WINDOW_WINDOW_C
