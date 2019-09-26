/*
 * This file is part of Fractol.

 * Fractol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Fractol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fractol. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#include "sdl_event_handler.hpp"

#include <iostream>

#include <SDL2/SDL.h>

namespace cozz {

SDLEventHandler::SDLEventHandler() {
    if (!SDL_WasInit(SDL_INIT_EVENTS)) {
        SDL_Init(SDL_INIT_EVENTS);
    }
}

namespace {

KeyMap AlignKeys(SDL_Scancode sdl_key) {
    static const std::map<SDL_Scancode, KeyMap> keys_map = {
        {SDL_SCANCODE_A, KeyMap::kA},
        {SDL_SCANCODE_B, KeyMap::kB},
        {SDL_SCANCODE_C, KeyMap::kC},
        {SDL_SCANCODE_D, KeyMap::kD},
        {SDL_SCANCODE_E, KeyMap::kE},
        {SDL_SCANCODE_F, KeyMap::kF},
        {SDL_SCANCODE_G, KeyMap::kG},
        {SDL_SCANCODE_H, KeyMap::kH},
        {SDL_SCANCODE_I, KeyMap::kI},
        {SDL_SCANCODE_J, KeyMap::kJ},
        {SDL_SCANCODE_K, KeyMap::kK},
        {SDL_SCANCODE_L, KeyMap::kL},
        {SDL_SCANCODE_M, KeyMap::kM},
        {SDL_SCANCODE_N, KeyMap::kN},
        {SDL_SCANCODE_O, KeyMap::kO},
        {SDL_SCANCODE_P, KeyMap::kP},
        {SDL_SCANCODE_Q, KeyMap::kQ},
        {SDL_SCANCODE_R, KeyMap::kR},
        {SDL_SCANCODE_S, KeyMap::kS},
        {SDL_SCANCODE_T, KeyMap::kT},
        {SDL_SCANCODE_U, KeyMap::kU},
        {SDL_SCANCODE_V, KeyMap::kV},
        {SDL_SCANCODE_W, KeyMap::kW},
        {SDL_SCANCODE_X, KeyMap::kX},
        {SDL_SCANCODE_Y, KeyMap::kY},
        {SDL_SCANCODE_Z, KeyMap::kZ},
        {SDL_SCANCODE_KP_A, KeyMap::kKeyPadA},
        {SDL_SCANCODE_KP_B, KeyMap::kKeyPadB},
        {SDL_SCANCODE_KP_C, KeyMap::kKeyPadC},
        {SDL_SCANCODE_KP_D, KeyMap::kKeyPadD},
        {SDL_SCANCODE_KP_E, KeyMap::kKeyPadE},
        {SDL_SCANCODE_KP_F, KeyMap::kKeyPadF},
        {SDL_SCANCODE_1, KeyMap::kNum1},
        {SDL_SCANCODE_2, KeyMap::kNum2},
        {SDL_SCANCODE_3, KeyMap::kNum3},
        {SDL_SCANCODE_4, KeyMap::kNum4},
        {SDL_SCANCODE_5, KeyMap::kNum5},
        {SDL_SCANCODE_6, KeyMap::kNum6},
        {SDL_SCANCODE_7, KeyMap::kNum7},
        {SDL_SCANCODE_8, KeyMap::kNum8},
        {SDL_SCANCODE_9, KeyMap::kNum9},
        {SDL_SCANCODE_0, KeyMap::kNum0},
        {SDL_SCANCODE_KP_1, KeyMap::kKeyPadNum1},
        {SDL_SCANCODE_KP_2, KeyMap::kKeyPadNum2},
        {SDL_SCANCODE_KP_3, KeyMap::kKeyPadNum3},
        {SDL_SCANCODE_KP_4, KeyMap::kKeyPadNum4},
        {SDL_SCANCODE_KP_5, KeyMap::kKeyPadNum5},
        {SDL_SCANCODE_KP_6, KeyMap::kKeyPadNum6},
        {SDL_SCANCODE_KP_7, KeyMap::kKeyPadNum7},
        {SDL_SCANCODE_KP_8, KeyMap::kKeyPadNum8},
        {SDL_SCANCODE_KP_9, KeyMap::kKeyPadNum9},
        {SDL_SCANCODE_KP_0, KeyMap::kKeyPadNum0},
        {SDL_SCANCODE_RETURN, KeyMap::kReturn},
        {SDL_SCANCODE_ESCAPE, KeyMap::kEscape},
        {SDL_SCANCODE_BACKSPACE, KeyMap::kBackSpace},
        {SDL_SCANCODE_TAB, KeyMap::kTab},
        {SDL_SCANCODE_SPACE, KeyMap::kSpace},
        {SDL_SCANCODE_MINUS, KeyMap::kMinus},
        {SDL_SCANCODE_EQUALS, KeyMap::kEquals},
        {SDL_SCANCODE_LEFTBRACKET, KeyMap::kLeftBracket},
        {SDL_SCANCODE_RIGHTBRACKET, KeyMap::kRightBracket},
        {SDL_SCANCODE_BACKSLASH, KeyMap::kBackSlash},
        {SDL_SCANCODE_CAPSLOCK, KeyMap::kCapsLock},
        {SDL_SCANCODE_NONUSHASH, KeyMap::kNonUsHash},
        {SDL_SCANCODE_SEMICOLON, KeyMap::kSemicolon},
        {SDL_SCANCODE_APOSTROPHE, KeyMap::kApostrophe},
        {SDL_SCANCODE_GRAVE, KeyMap::kGrave},
        {SDL_SCANCODE_COMMA, KeyMap::kComma},
        {SDL_SCANCODE_PERIOD, KeyMap::kPeriod},
        {SDL_SCANCODE_SLASH, KeyMap::kSlash},
        {SDL_SCANCODE_F1, KeyMap::kF1},
        {SDL_SCANCODE_F2, KeyMap::kF2},
        {SDL_SCANCODE_F3, KeyMap::kF3},
        {SDL_SCANCODE_F4, KeyMap::kF4},
        {SDL_SCANCODE_F5, KeyMap::kF5},
        {SDL_SCANCODE_F6, KeyMap::kF6},
        {SDL_SCANCODE_F7, KeyMap::kF7},
        {SDL_SCANCODE_F8, KeyMap::kF8},
        {SDL_SCANCODE_F9, KeyMap::kF9},
        {SDL_SCANCODE_F10, KeyMap::kF10},
        {SDL_SCANCODE_F11, KeyMap::kF11},
        {SDL_SCANCODE_F12, KeyMap::kF12},
        {SDL_SCANCODE_F13, KeyMap::kF13},
        {SDL_SCANCODE_F14, KeyMap::kF14},
        {SDL_SCANCODE_F15, KeyMap::kF15},
        {SDL_SCANCODE_F16, KeyMap::kF16},
        {SDL_SCANCODE_F17, KeyMap::kF17},
        {SDL_SCANCODE_F18, KeyMap::kF18},
        {SDL_SCANCODE_F19, KeyMap::kF19},
        {SDL_SCANCODE_F20, KeyMap::kF20},
        {SDL_SCANCODE_F21, KeyMap::kF21},
        {SDL_SCANCODE_F22, KeyMap::kF22},
        {SDL_SCANCODE_F23, KeyMap::kF23},
        {SDL_SCANCODE_F24, KeyMap::kF24},
        {SDL_SCANCODE_PRINTSCREEN, KeyMap::kPrintScreen},
        {SDL_SCANCODE_SCROLLLOCK, KeyMap::kScrollLock},
        {SDL_SCANCODE_PAUSE, KeyMap::kPause},
        {SDL_SCANCODE_INSERT, KeyMap::kInsert},
        {SDL_SCANCODE_HOME, KeyMap::kHome},
        {SDL_SCANCODE_PAGEUP, KeyMap::kPageUp},
        {SDL_SCANCODE_DELETE, KeyMap::kDelete},
        {SDL_SCANCODE_END, KeyMap::kEnd},
        {SDL_SCANCODE_PAGEDOWN, KeyMap::kPageDown},
        {SDL_SCANCODE_RIGHT, KeyMap::kRight},
        {SDL_SCANCODE_LEFT, KeyMap::kLeft},
        {SDL_SCANCODE_DOWN, KeyMap::kDown},
        {SDL_SCANCODE_UP, KeyMap::kUp},
        {SDL_SCANCODE_NUMLOCKCLEAR, KeyMap::kNumLockClear},
        {SDL_SCANCODE_KP_DIVIDE, KeyMap::kKeyPadDivide},
        {SDL_SCANCODE_KP_MULTIPLY, KeyMap::kKeyPadMultiply},
        {SDL_SCANCODE_KP_MINUS, KeyMap::kKeyPadMinus},
        {SDL_SCANCODE_KP_PLUS, KeyMap::kKeyPadPlus},
        {SDL_SCANCODE_KP_ENTER, KeyMap::kKeyPadEnter},
        {SDL_SCANCODE_KP_PERIOD, KeyMap::kKeyPadPeriod},
        {SDL_SCANCODE_KP_EQUALS, KeyMap::kKeyPadEquals},
        {SDL_SCANCODE_KP_COMMA, KeyMap::kKeyPadComma},
        {SDL_SCANCODE_KP_LEFTPAREN, KeyMap::kKeyPadLeftParenthesis},
        {SDL_SCANCODE_KP_RIGHTPAREN, KeyMap::kKeyPadRightParenthesis},
        {SDL_SCANCODE_KP_LEFTBRACE, KeyMap::kKeyPadLeftBrace},
        {SDL_SCANCODE_KP_RIGHTBRACE, KeyMap::kKeyPadRightBrace},
        {SDL_SCANCODE_KP_TAB, KeyMap::kKeyPadTab},
        {SDL_SCANCODE_KP_BACKSPACE, KeyMap::kKeyPadBackSpace},
        {SDL_SCANCODE_KP_XOR, KeyMap::kKeyPadXOR},
        {SDL_SCANCODE_KP_POWER, KeyMap::kKeyPadPower},
        {SDL_SCANCODE_KP_PERCENT, KeyMap::kKeyPadPercent},
        {SDL_SCANCODE_KP_LESS, KeyMap::kKeyPadLess},
        {SDL_SCANCODE_KP_GREATER, KeyMap::kKeyPadGreater},
        {SDL_SCANCODE_KP_AMPERSAND, KeyMap::kKeyPadAmpersand},
        {SDL_SCANCODE_KP_DBLAMPERSAND, KeyMap::kKeyPadDoubleAmpersand},
        {SDL_SCANCODE_KP_VERTICALBAR, KeyMap::kKeyPadVerticalBar},
        {SDL_SCANCODE_KP_DBLVERTICALBAR, KeyMap::kKeyPadDoubleVerticalBar},
        {SDL_SCANCODE_KP_COLON, KeyMap::kKeyPadColon},
        {SDL_SCANCODE_KP_HASH, KeyMap::kKeyPadHash},
        {SDL_SCANCODE_KP_SPACE, KeyMap::kKeyPadSpace},
        {SDL_SCANCODE_NONUSBACKSLASH, KeyMap::kNonUsBackSlash},
        {SDL_SCANCODE_APPLICATION, KeyMap::kApplication},
        {SDL_SCANCODE_POWER, KeyMap::kPower},
        {SDL_SCANCODE_EXECUTE, KeyMap::kExecute},
        {SDL_SCANCODE_HELP, KeyMap::kHelp},
        {SDL_SCANCODE_MENU, KeyMap::kMenu},
        {SDL_SCANCODE_SELECT, KeyMap::kSelect},
        {SDL_SCANCODE_STOP, KeyMap::kStop},
        {SDL_SCANCODE_AGAIN, KeyMap::kAgain},
        {SDL_SCANCODE_UNDO, KeyMap::kUndo},
        {SDL_SCANCODE_CUT, KeyMap::kCut},
        {SDL_SCANCODE_COPY, KeyMap::kCopy},
        {SDL_SCANCODE_PASTE, KeyMap::kPaste},
        {SDL_SCANCODE_FIND, KeyMap::kFind},
        {SDL_SCANCODE_MUTE, KeyMap::kMute},
        {SDL_SCANCODE_VOLUMEUP, KeyMap::kVolumeUp},
        {SDL_SCANCODE_VOLUMEDOWN, KeyMap::kVolumeDown},
        {SDL_SCANCODE_LCTRL, KeyMap::kLCtrl},
        {SDL_SCANCODE_LSHIFT, KeyMap::kLShift},
        {SDL_SCANCODE_LALT, KeyMap::kLalt},
        {SDL_SCANCODE_LGUI, KeyMap::kLGui},
        {SDL_SCANCODE_RCTRL, KeyMap::kRctrl},
        {SDL_SCANCODE_RSHIFT, KeyMap::kRShift},
        {SDL_SCANCODE_RALT, KeyMap::kRalt},
        {SDL_SCANCODE_RGUI, KeyMap::kRGui},
        {SDL_SCANCODE_MODE, KeyMap::kMode},
    };

    try {
        return keys_map.at(sdl_key);
    } catch (const std::out_of_range&) {
        return KeyMap::kUnknown;
    }
}

MouseMotionEvent::ButtonState AlignMouseButtonState(uint32_t sdl_state) {
    MouseMotionEvent::ButtonState state = MouseMotionEvent::ButtonState::kReleased;

    if (sdl_state & SDL_BUTTON_LMASK)
        state |= MouseMotionEvent::ButtonState::kLeftPressed;
    if (sdl_state & SDL_BUTTON_MMASK)
        state |= MouseMotionEvent::ButtonState::kMiddlePressed;
    if (sdl_state & SDL_BUTTON_RMASK)
        state |= MouseMotionEvent::ButtonState::kRightPressed;
    if (sdl_state & SDL_BUTTON_X1MASK)
        state |= MouseMotionEvent::ButtonState::kExtra1Pressed;
    if (sdl_state & SDL_BUTTON_X2MASK)
        state |= MouseMotionEvent::ButtonState::kExtra2Pressed;
    return state;
}

KeyMap AlignMouseButtons(uint8_t sdl_button) {
    static const std::map<uint8_t, KeyMap> buttons_map = {
        {SDL_BUTTON_LEFT, KeyMap::kLeftMouseButton},   {SDL_BUTTON_MIDDLE, KeyMap::kMiddleMouseButton},
        {SDL_BUTTON_RIGHT, KeyMap::kRightMouseButton}, {SDL_BUTTON_X1, KeyMap::kExtra1MouseButton},
        {SDL_BUTTON_X2, KeyMap::kExtra2MouseButton},
    };

    try {
        return buttons_map.at(sdl_button);
    } catch (const std::out_of_range&) {
        return KeyMap::kUnknown;
    }
}

}  // namespace

bool SDLEventHandler::Poll() const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_WINDOWEVENT:
                switch (e.window.event) {
                    case SDL_WINDOWEVENT_SHOWN:
                        TriggerCallbacks(WindowShownEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_HIDDEN:
                        TriggerCallbacks(WindowHiddenEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_EXPOSED:
                        TriggerCallbacks(WindowExposedEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_MOVED:
                        TriggerCallbacks(WindowMovedEvent(e.window.windowID, e.window.data1, e.window.data2));
                        break;
                    case SDL_WINDOWEVENT_RESIZED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        TriggerCallbacks(WindowResizedEvent(e.window.windowID, e.window.data1, e.window.data2));
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED:
                        TriggerCallbacks(WindowMinimizedEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        TriggerCallbacks(WindowMaximizedEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_RESTORED:
                        TriggerCallbacks(WindowRestoredEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                        TriggerCallbacks(WindowEnterEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_LEAVE:
                        TriggerCallbacks(WindowLeaveEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        TriggerCallbacks(WindowFocusGainedEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        TriggerCallbacks(WindowFocusLostEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        TriggerCallbacks(WindowCloseEvent(e.window.windowID));
                        break;
                    case SDL_WINDOWEVENT_TAKE_FOCUS:
                        TriggerCallbacks(WindowTakeFocusEvent(e.window.windowID));
                        break;
                    default:
                        return false;
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                TriggerCallbacks(KeyboardEvent(e.key.windowID, e.key.state == SDL_PRESSED, e.key.repeat,
                                               AlignKeys(e.key.keysym.scancode)));
                break;
            case SDL_MOUSEMOTION:
                TriggerCallbacks(
                    MouseMotionEvent(e.motion.windowID, AlignMouseButtonState(e.motion.state), e.motion.x, e.motion.y));
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                TriggerCallbacks(MouseButtonEvent(e.button.windowID, AlignMouseButtons(e.button.button),
                                                  e.button.state == SDL_PRESSED, e.button.clicks, e.button.x,
                                                  e.button.y));
                break;
            case SDL_MOUSEWHEEL:
                TriggerCallbacks(MouseWheelEvent(e.wheel.windowID, e.wheel.x, e.wheel.y,
                                                 e.wheel.direction == SDL_MOUSEWHEEL_FLIPPED));
                break;
            case SDL_QUIT:
                TriggerCallbacks(QuitEvent());
                break;
            default:
                return false;
        }
    }
    return true;
}

}  // namespace cozz
