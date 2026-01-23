#ifndef P_SYSTEM_WIN32_CONSOLE_CONSOLE_C
#define P_SYSTEM_WIN32_CONSOLE_CONSOLE_C

#include "console.h"

static PConsoleKeybdKey pWin32ConsoleConvertKey(WORD key_code, CHAR key_char)
{
    switch (key_char) {
        case 'a': return PConsoleKeybd_A; break;
        case 'b': return PConsoleKeybd_B; break;
        case 'c': return PConsoleKeybd_C; break;
        case 'd': return PConsoleKeybd_D; break;
        case 'e': return PConsoleKeybd_E; break;
        case 'f': return PConsoleKeybd_F; break;
        case 'g': return PConsoleKeybd_G; break;
        case 'h': return PConsoleKeybd_H; break;
        case 'i': return PConsoleKeybd_I; break;
        case 'j': return PConsoleKeybd_J; break;
        case 'k': return PConsoleKeybd_K; break;
        case 'l': return PConsoleKeybd_L; break;
        case 'm': return PConsoleKeybd_M; break;
        case 'n': return PConsoleKeybd_N; break;
        case 'o': return PConsoleKeybd_O; break;
        case 'p': return PConsoleKeybd_P; break;
        case 'q': return PConsoleKeybd_Q; break;
        case 'r': return PConsoleKeybd_R; break;
        case 's': return PConsoleKeybd_S; break;
        case 't': return PConsoleKeybd_T; break;
        case 'u': return PConsoleKeybd_U; break;
        case 'v': return PConsoleKeybd_V; break;
        case 'w': return PConsoleKeybd_W; break;
        case 'x': return PConsoleKeybd_X; break;
        case 'y': return PConsoleKeybd_Y; break;
        case 'z': return PConsoleKeybd_Z; break;
        case '0': return PConsoleKeybd_0; break;
        case '1': return PConsoleKeybd_1; break;
        case '2': return PConsoleKeybd_2; break;
        case '3': return PConsoleKeybd_3; break;
        case '4': return PConsoleKeybd_4; break;
        case '5': return PConsoleKeybd_5; break;
        case '6': return PConsoleKeybd_6; break;
        case '7': return PConsoleKeybd_7; break;
        case '8': return PConsoleKeybd_8; break;
        case '9': return PConsoleKeybd_9; break;

        default: break;
    }

    switch (key_code) {
        case VK_SPACE:       return PConsoleKeybd_Space;        break;
        case VK_OEM_MINUS:   return PConsoleKeybd_Minus;        break;
        case VK_OEM_PLUS:    return PConsoleKeybd_Equal;        break;
        case VK_OEM_4:       return PConsoleKeybd_SquareLeft;   break;
        case VK_OEM_6:       return PConsoleKeybd_SquareRight;  break;
        case VK_OEM_5:       return PConsoleKeybd_BackSlash;    break;
        case VK_OEM_1:       return PConsoleKeybd_SemiColon;    break;
        case VK_OEM_7:       return PConsoleKeybd_Apostrophe;   break;
        case VK_OEM_3:       return PConsoleKeybd_Grave;        break;
        case VK_OEM_COMMA:   return PConsoleKeybd_Comma;        break;
        case VK_OEM_PERIOD:  return PConsoleKeybd_Period;       break;
        case VK_OEM_2:       return PConsoleKeybd_Slash;        break;
        case VK_UP:          return PConsoleKeybd_Up;           break;
        case VK_DOWN:        return PConsoleKeybd_Down;         break;
        case VK_LEFT:        return PConsoleKeybd_Left;         break;
        case VK_RIGHT:       return PConsoleKeybd_Right;        break;
        case VK_HOME:        return PConsoleKeybd_Home;         break;
        case VK_END:         return PConsoleKeybd_End;          break;
        case VK_PRIOR:       return PConsoleKeybd_PageUp;       break;
        case VK_NEXT:        return PConsoleKeybd_PageDown;     break;
        case VK_INSERT:      return PConsoleKeybd_Insert;       break;
        case VK_DELETE:      return PConsoleKeybd_Delete;       break;
        case VK_F1:          return PConsoleKeybd_F1;           break;
        case VK_F2:          return PConsoleKeybd_F2;           break;
        case VK_F3:          return PConsoleKeybd_F3;           break;
        case VK_F4:          return PConsoleKeybd_F4;           break;
        case VK_F5:          return PConsoleKeybd_F5;           break;
        case VK_F6:          return PConsoleKeybd_F6;           break;
        case VK_F7:          return PConsoleKeybd_F7;           break;
        case VK_F8:          return PConsoleKeybd_F8;           break;
        case VK_F9:          return PConsoleKeybd_F9;           break;
        case VK_F10:         return PConsoleKeybd_F10;          break;
        case VK_F11:         return PConsoleKeybd_F11;          break;
        case VK_F12:         return PConsoleKeybd_F12;          break;
        case VK_RETURN:      return PConsoleKeybd_Enter;        break;
        case VK_ESCAPE:      return PConsoleKeybd_Escape;       break;
        case VK_BACK:        return PConsoleKeybd_BackSpace;    break;
        case VK_TAB:         return PConsoleKeybd_Tab;          break;

        default: break;
    }

    return PConsoleKeybd_None;
}

static Bool pWin32ConsoleModeSetCooked(PWin32Console* self)
{
    if (self->mode != PConsoleMode_Cooked) {
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), self->conf_in);
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), self->conf_out);

        self->mode = PConsoleMode_Cooked;
    }

    return 1;
}

static Bool pWin32ConsoleModeSetRaw(PWin32Console* self)
{
    Int conf_in = self->conf_in & ~(ENABLE_PROCESSED_INPUT |
        ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

    Int conf_out = self->conf_out | (ENABLE_PROCESSED_OUTPUT |
        ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);

    if (self->mode != PConsoleMode_Raw) {
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), conf_in);
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), conf_out);

        self->mode = PConsoleMode_Raw;
    }

    return 1;
}

PWin32Console* pWin32ConsoleReserve(PMemoryArena* arena)
{
    return pMemoryArenaReserveOneOf(arena, PWin32Console);
}

Bool pWin32ConsoleCreate(PWin32Console* self)
{
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), (DWORD*) &self->conf_in);
    GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), (DWORD*) &self->conf_out);

    self->mode = PConsoleMode_Cooked;

    return 1;
}

void pWin32ConsoleDestroy(PWin32Console* self)
{
    if (self->mode != PConsoleMode_Cooked)
        pWin32ConsoleModeSetCooked(self);

    pMemorySet(self, sizeof *self, 0xAB);
}

Bool pWin32ConsoleModeSet(PWin32Console* self, PConsoleMode mode)
{
    switch (mode) {
        case PConsoleMode_Cooked: return pWin32ConsoleModeSetCooked(self);
        case PConsoleMode_Raw:    return pWin32ConsoleModeSetRaw(self);

        default: break;
    }

    return 0;
}

PConsoleMode pWin32ConsoleModeGet(PWin32Console* self)
{
    return self->mode;
}

Int pWin32ConsoleWrite(PWin32Console* self, U8* pntr, Int start, Int stop)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int result = 0;

    while (result < size) {
        Int count = 0;

        Bool status = WriteFile(handle, memory + result,
            size - result, (DWORD*) &count, NULL);

        if (status != 0 && count > 0 && count <= size - result)
            result += count;
        else
            break;
    }

    return result;
}

Int pWin32ConsoleRead(PWin32Console* self, U8* pntr, Int start, Int stop)
{
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);

    I8* memory = ((I8*) pntr + start);
    Int size   = stop - start;
    Int count  = 0;

    Bool status = ReadFile(handle, memory, size, (DWORD*) &count, NULL);

    if (status != 0 && count > 0 && count <= size) return count;

    return 0;
}

Bool pWin32ConsolePollEvent(PWin32Console* self, PConsoleEvent* event)
{
    INPUT_RECORD record;

    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD  count  = 0;

    if (GetNumberOfConsoleInputEvents(handle, &count) == 0 || count <= 0)
        return 0;

    if (ReadConsoleInput(handle, &record, 1, &count) == 0 || count <= 0)
        return 0;

    if (record.EventType == KEY_EVENT) {
        WORD key_code  = record.Event.KeyEvent.wVirtualKeyCode;
        CHAR key_char  = record.Event.KeyEvent.uChar.AsciiChar;

        PConsoleKeybdKey key = pWin32ConsoleConvertKey(key_code, key_char);

        if (record.Event.KeyEvent.bKeyDown != 0) {
            if (event != NULL)
                *event = pConsoleEventKeybdKey(key);

            return 1;
        }
    }

    return 0;
}

#endif // P_CONSOLE_CONSOLE_C
