#ifndef P_SYSTEM_WIN32_WINDOW_EVENT_C
#define P_SYSTEM_WIN32_WINDOW_EVENT_C

#include "event.h"

PWindowKeybdKey pWin32WindowConvertKey(WORD key_code)
{
    switch (key_code) {
        case 'A':            return PWindowKeybd_A;
        case 'B':            return PWindowKeybd_B;
        case 'C':            return PWindowKeybd_C;
        case 'D':            return PWindowKeybd_D;
        case 'E':            return PWindowKeybd_E;
        case 'F':            return PWindowKeybd_F;
        case 'G':            return PWindowKeybd_G;
        case 'H':            return PWindowKeybd_H;
        case 'I':            return PWindowKeybd_I;
        case 'J':            return PWindowKeybd_J;
        case 'K':            return PWindowKeybd_K;
        case 'L':            return PWindowKeybd_L;
        case 'M':            return PWindowKeybd_M;
        case 'N':            return PWindowKeybd_N;
        case 'O':            return PWindowKeybd_O;
        case 'P':            return PWindowKeybd_P;
        case 'Q':            return PWindowKeybd_Q;
        case 'R':            return PWindowKeybd_R;
        case 'S':            return PWindowKeybd_S;
        case 'T':            return PWindowKeybd_T;
        case 'U':            return PWindowKeybd_U;
        case 'V':            return PWindowKeybd_V;
        case 'W':            return PWindowKeybd_W;
        case 'X':            return PWindowKeybd_X;
        case 'Y':            return PWindowKeybd_Y;
        case 'Z':            return PWindowKeybd_Z;
        case '0':            return PWindowKeybd_0;
        case '1':            return PWindowKeybd_1;
        case '2':            return PWindowKeybd_2;
        case '3':            return PWindowKeybd_3;
        case '4':            return PWindowKeybd_4;
        case '5':            return PWindowKeybd_5;
        case '6':            return PWindowKeybd_6;
        case '7':            return PWindowKeybd_7;
        case '8':            return PWindowKeybd_8;
        case '9':            return PWindowKeybd_9;
        case VK_SPACE:       return PWindowKeybd_Space;
        case VK_OEM_MINUS:   return PWindowKeybd_Minus;
        case VK_OEM_PLUS:    return PWindowKeybd_Equal;
        case VK_OEM_4:       return PWindowKeybd_SquareLeft;
        case VK_OEM_6:       return PWindowKeybd_SquareRight;
        case VK_OEM_5:       return PWindowKeybd_BackSlash;
        case VK_OEM_1:       return PWindowKeybd_SemiColon;
        case VK_OEM_7:       return PWindowKeybd_Apostrophe;
        case VK_OEM_3:       return PWindowKeybd_Grave;
        case VK_OEM_COMMA:   return PWindowKeybd_Comma;
        case VK_OEM_PERIOD:  return PWindowKeybd_Period;
        case VK_OEM_2:       return PWindowKeybd_Slash;
        case VK_UP:          return PWindowKeybd_Up;
        case VK_DOWN:        return PWindowKeybd_Down;
        case VK_LEFT:        return PWindowKeybd_Left;
        case VK_RIGHT:       return PWindowKeybd_Right;
        case VK_HOME:        return PWindowKeybd_Home;
        case VK_END:         return PWindowKeybd_End;
        case VK_PRIOR:       return PWindowKeybd_PageUp;
        case VK_NEXT:        return PWindowKeybd_PageDown;
        case VK_INSERT:      return PWindowKeybd_Insert;
        case VK_DELETE:      return PWindowKeybd_Delete;
        case VK_F1:          return PWindowKeybd_F1;
        case VK_F2:          return PWindowKeybd_F2;
        case VK_F3:          return PWindowKeybd_F3;
        case VK_F4:          return PWindowKeybd_F4;
        case VK_F5:          return PWindowKeybd_F5;
        case VK_F6:          return PWindowKeybd_F6;
        case VK_F7:          return PWindowKeybd_F7;
        case VK_F8:          return PWindowKeybd_F8;
        case VK_F9:          return PWindowKeybd_F9;
        case VK_F10:         return PWindowKeybd_F10;
        case VK_F11:         return PWindowKeybd_F11;
        case VK_F12:         return PWindowKeybd_F12;
        case VK_RETURN:      return PWindowKeybd_Enter;
        case VK_ESCAPE:      return PWindowKeybd_Escape;
        case VK_BACK:        return PWindowKeybd_BackSpace;
        case VK_TAB:         return PWindowKeybd_Tab;

        default: break;
    }

    return PWindowKeybd_None;
}

#endif
