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

#include "fractol.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>

#include <SDL2/SDL.h>

#include "sdl_event_handler.hpp"

namespace cozz {

Fractol::Fractol(int argc, char** argv) : is_running_(true), event_handler_(std::make_unique<SDLEventHandler>()) {
    auto win_p = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, 0);

    event_handler_->RegisterEventCallback<MouseWheelEvent>(
        std::bind(&Fractol::MouseWheelHandler, this, std::placeholders::_1));
    event_handler_->RegisterEventCallback<MouseButtonEvent>(
        std::bind(&Fractol::MouseButtonHandler, this, std::placeholders::_1));
    event_handler_->RegisterEventCallback<MouseMotionEvent>(
        std::bind(&Fractol::MouseMotionHandler, this, std::placeholders::_1));
    event_handler_->RegisterEventCallback<KeyboardEvent>(
        std::bind(&Fractol::KeyboardHandler, this, std::placeholders::_1));
    event_handler_->RegisterEventCallback<QuitEvent>(std::bind(&Fractol::Terminate, this, std::placeholders::_1));
}

Fractol::~Fractol() = default;

void Fractol::MouseWheelHandler(const MouseWheelEvent& event) {
    std::cout << "Wheel scrolled by x: " << event.GetScrolledByX() << ", by y: " << event.GetScrolledByY()
              << "; inversed: " << event.IsInversed() << std::endl;
}

void Fractol::MouseButtonHandler(const MouseButtonEvent& event) {
    auto mouse_pos = event.GetPosition();

    std::cout << "Mouse at: " << mouse_pos.first << ":" << mouse_pos.second << "; ";
    switch (event.GetButton()) {
        case KeyMap::kLeftMouseButton:
            std::cout << "LBM";
            break;
        case KeyMap::kMiddleMouseButton:
            std::cout << "MBM";
            break;
        case KeyMap::kRightMouseButton:
            std::cout << "RBM";
            break;
        case KeyMap::kExtra1MouseButton:
            std::cout << "X1BM";
            break;
        case KeyMap::kExtra2MouseButton:
            std::cout << "X2BM";
            break;
    }
    if (event.IsPressed()) {
        std::cout << " clicked ";
    } else {
        std::cout << " released after ";
    }
    std::cout << static_cast<uint16_t>(event.GetClicksCount()) << " times;" << std::endl;
}

void Fractol::MouseMotionHandler(const MouseMotionEvent& event) {
    auto mouse_pos = event.GetPosition();

    std::cout << "Mouse at: " << mouse_pos.first << ":" << mouse_pos.second << "; ";
    if (event.IsLeftButtonPressed()) {
        std::cout << "LBM pressed; ";
    }
    if (event.IsMiddleButtonPressed()) {
        std::cout << "MBM pressed; ";
    }
    if (event.IsRightButtonPressed()) {
        std::cout << "RBM pressed; ";
    }
    if (event.IsExtra1ButtonPressed()) {
        std::cout << "X1BM pressed; ";
    }
    if (event.IsExtra2ButtonPressed()) {
        std::cout << "X2BM pressed; ";
    }
    std::cout << std::endl;
}

void Fractol::KeyboardHandler(const KeyboardEvent& event) {
    char symb;
    KeyMap key = event.GetKey();
    if (key > KeyMap::kAlphabeticalKeysBegin && key < KeyMap::kAlphabeticalKeysEnd) {
        symb = static_cast<char>(static_cast<uint16_t>(key) - static_cast<uint16_t>(KeyMap::kA)) + 'A';
    } else if (key > KeyMap::kNumericKeysBegin && key < KeyMap::kNumericKeysEnd) {
        symb = static_cast<char>(static_cast<uint16_t>(key) - static_cast<uint16_t>(KeyMap::kNum0)) + '0';
    }

    if (event.IsPressed()) {
        std::cout << "Key '" << symb << "' pressed" << std::endl;
    } else {
        std::cout << "Key '" << symb << "' released" << std::endl;
    }
}

void Fractol::Terminate(const QuitEvent& event) {
    std::cout << "Application is terminating" << std::endl;
    is_running_ = false;
}

uint8_t Fractol::Run() {
    while (is_running_) {
        event_handler_->Poll();
    }
}

}  // namespace cozz
