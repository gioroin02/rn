#ifndef RHO_SYSTEM_WINDOW_WIN32_EVENT_C
#define RHO_SYSTEM_WINDOW_WIN32_EVENT_C

#include "event.h"

RWindowKeyboardKey rho_win32_window_convert_key(WORD key_code)
{
    switch (key_code) {
        case 'A':            return RWindowKeyboard_A;
        case 'B':            return RWindowKeyboard_B;
        case 'C':            return RWindowKeyboard_C;
        case 'D':            return RWindowKeyboard_D;
        case 'E':            return RWindowKeyboard_E;
        case 'F':            return RWindowKeyboard_F;
        case 'G':            return RWindowKeyboard_G;
        case 'H':            return RWindowKeyboard_H;
        case 'I':            return RWindowKeyboard_I;
        case 'J':            return RWindowKeyboard_J;
        case 'K':            return RWindowKeyboard_K;
        case 'L':            return RWindowKeyboard_L;
        case 'M':            return RWindowKeyboard_M;
        case 'N':            return RWindowKeyboard_N;
        case 'O':            return RWindowKeyboard_O;
        case 'P':            return RWindowKeyboard_P;
        case 'Q':            return RWindowKeyboard_Q;
        case 'R':            return RWindowKeyboard_R;
        case 'S':            return RWindowKeyboard_S;
        case 'T':            return RWindowKeyboard_T;
        case 'U':            return RWindowKeyboard_U;
        case 'V':            return RWindowKeyboard_V;
        case 'W':            return RWindowKeyboard_W;
        case 'X':            return RWindowKeyboard_X;
        case 'Y':            return RWindowKeyboard_Y;
        case 'Z':            return RWindowKeyboard_Z;
        case '0':            return RWindowKeyboard_0;
        case '1':            return RWindowKeyboard_1;
        case '2':            return RWindowKeyboard_2;
        case '3':            return RWindowKeyboard_3;
        case '4':            return RWindowKeyboard_4;
        case '5':            return RWindowKeyboard_5;
        case '6':            return RWindowKeyboard_6;
        case '7':            return RWindowKeyboard_7;
        case '8':            return RWindowKeyboard_8;
        case '9':            return RWindowKeyboard_9;
        case VK_SPACE:       return RWindowKeyboard_Space;
        case VK_OEM_MINUS:   return RWindowKeyboard_Minus;
        case VK_OEM_PLUS:    return RWindowKeyboard_Equal;
        case VK_OEM_4:       return RWindowKeyboard_SquareLeft;
        case VK_OEM_6:       return RWindowKeyboard_SquareRight;
        case VK_OEM_5:       return RWindowKeyboard_BackSlash;
        case VK_OEM_1:       return RWindowKeyboard_SemiColon;
        case VK_OEM_7:       return RWindowKeyboard_Apostrophe;
        case VK_OEM_3:       return RWindowKeyboard_Grave;
        case VK_OEM_COMMA:   return RWindowKeyboard_Comma;
        case VK_OEM_PERIOD:  return RWindowKeyboard_Period;
        case VK_OEM_2:       return RWindowKeyboard_Slash;
        case VK_UP:          return RWindowKeyboard_Up;
        case VK_DOWN:        return RWindowKeyboard_Down;
        case VK_LEFT:        return RWindowKeyboard_Left;
        case VK_RIGHT:       return RWindowKeyboard_Right;
        case VK_HOME:        return RWindowKeyboard_Home;
        case VK_END:         return RWindowKeyboard_End;
        case VK_PRIOR:       return RWindowKeyboard_PageUp;
        case VK_NEXT:        return RWindowKeyboard_PageDown;
        case VK_INSERT:      return RWindowKeyboard_Insert;
        case VK_DELETE:      return RWindowKeyboard_Delete;
        case VK_F1:          return RWindowKeyboard_F1;
        case VK_F2:          return RWindowKeyboard_F2;
        case VK_F3:          return RWindowKeyboard_F3;
        case VK_F4:          return RWindowKeyboard_F4;
        case VK_F5:          return RWindowKeyboard_F5;
        case VK_F6:          return RWindowKeyboard_F6;
        case VK_F7:          return RWindowKeyboard_F7;
        case VK_F8:          return RWindowKeyboard_F8;
        case VK_F9:          return RWindowKeyboard_F9;
        case VK_F10:         return RWindowKeyboard_F10;
        case VK_F11:         return RWindowKeyboard_F11;
        case VK_F12:         return RWindowKeyboard_F12;
        case VK_RETURN:      return RWindowKeyboard_Enter;
        case VK_ESCAPE:      return RWindowKeyboard_Escape;
        case VK_BACK:        return RWindowKeyboard_BackSpace;
        case VK_TAB:         return RWindowKeyboard_Tab;

        default: break;
    }

    return RWindowKeyboard_None;
}

#endif
