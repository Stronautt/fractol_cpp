/*
 * This file is part of LibZZgraph.

 * LibZZgraph is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZgraph is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZgraph. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef LIBZZGRAPH_INCLUDE_KEY_MAP_EVENT_HPP_
#define LIBZZGRAPH_INCLUDE_KEY_MAP_EVENT_HPP_

namespace cozz {

/* clang-format off */
enum class KeyMap : uint16_t {
    kUnknown = 0x0,

    kKeyboardButtonsBegin,

    kAlphabeticalKeysBegin,

    /* Alphabetical letter keys */
    kA, kB, kC, kD, kE, kF, kG, kH, kI, kJ, kK, kL, kM,
    kN, kO, kP, kQ, kR, kS, kT, kU, kV, kW, kX, kY, kZ,

    /* Key pad alphabetical letter keys */
    kKeyPadA, kKeyPadB, kKeyPadC, kKeyPadD, kKeyPadE, kKeyPadF,

    kAlphabeticalKeysEnd,

    kNumericKeysBegin,

    /* Numeric keys */
    kNum0, kNum1, kNum2, kNum3, kNum4,
    kNum5, kNum6, kNum7, kNum8, kNum9,

    /* Key pad numeric keys */
    kKeyPadNum1, kKeyPadNum2, kKeyPadNum3, kKeyPadNum4, kKeyPadNum5,
    kKeyPadNum6, kKeyPadNum7, kKeyPadNum8, kKeyPadNum9, kKeyPadNum0,

    kNumericKeysEnd,

    kReturn, kEscape, kBackSpace, kTab, kSpace,

    kMinus, kEquals, kLeftBracket, kRightBracket, kBackSlash, kCapsLock,

    kNonUsHash, kSemicolon, kApostrophe, kGrave, kComma, kPeriod, kSlash,

    kFunctionalKeysBegin,

    /* Functional keys */
    kF1, kF2, kF3, kF4, kF5, kF6, kF7, kF8, kF9, kF10, kF11, kF12,
    kF13, kF14, kF15, kF16, kF17, kF18, kF19, kF20, kF21, kF22, kF23, kF24,

    kFunctionalKeysEnd,

    kPrintScreen, kScrollLock, kPause, kInsert,

    kHome, kPageUp, kDelete, kEnd, kPageDown, kRight, kLeft, kDown, kUp,

    /* Key pad functional keys */
    kNumLockClear, kKeyPadDivide, kKeyPadMultiply, kKeyPadMinus, kKeyPadPlus,
    kKeyPadEnter, kKeyPadPeriod, kKeyPadEquals, kKeyPadComma, kKeyPadLeftParenthesis,
    kKeyPadRightParenthesis, kKeyPadLeftBrace, kKeyPadRightBrace, kKeyPadTab,
    kKeyPadBackSpace, kKeyPadXOR, kKeyPadPower, kKeyPadPercent, kKeyPadLess,
    kKeyPadGreater, kKeyPadAmpersand, kKeyPadDoubleAmpersand, kKeyPadVerticalBar,
    kKeyPadDoubleVerticalBar, kKeyPadColon, kKeyPadHash, kKeyPadSpace,

    kNonUsBackSlash, kApplication, kPower,

    kExecute, kHelp, kMenu, kSelect, kStop, kAgain, kUndo, kCut, kCopy, kPaste, kFind, kMute, kVolumeUp, kVolumeDown,

    kLCtrl, kLShift, kLalt, kLGui, kRctrl, kRShift, kRalt, kRGui, kMode,

    kKeyboardButtonsEnd,

    kMouseButtonsBegin,

    kLeftMouseButton, kMiddleMouseButton, kRightMouseButton, kExtra1MouseButton, kExtra2MouseButton,

    kMouseButtonsEnd,
};
/* clang-format on */

}  // namespace cozz

#endif  // LIBZZGRAPH_INCLUDE_KEY_MAP_EVENT_HPP_
