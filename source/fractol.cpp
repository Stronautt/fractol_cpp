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

#include "canvas.hpp"
#include "font_resource.hpp"
#include "painter.hpp"
#include "resource_manager.hpp"
#include "sdl_event_handler.hpp"
#include "sdl_window.hpp"
#include "windows_manager.hpp"

namespace cozz {

Fractol::Fractol(int, char**)
    : is_running_(true),
      resource_manager_(std::make_shared<ResourceManager>()),
      event_handler_(std::make_shared<SDLEventHandler>()),
      windows_manager_(std::make_shared<WindowsManager>(event_handler_)) {
    resource_manager_->LoadFont("Ubuntu24", "resources/fonts/ubuntu.ttf", 24);

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
        default:
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
    static std::pair<uint64_t, uint64_t> old_mouse_pos;
    auto mouse_pos = event.GetPosition();

    std::cout << "Mouse at: " << mouse_pos.first << ":" << mouse_pos.second << "; ";
    if (event.IsLeftButtonPressed()) {
        std::cout << "LBM pressed; ";

        Painter painter(windows_manager_->GetById(event.GetWindowId()).lock()->GetCanvas());

        painter.DrawLine({old_mouse_pos.first, old_mouse_pos.second}, {mouse_pos.first, mouse_pos.second},
                         {0xFF, 0x00, 0x00}, 2);

        old_mouse_pos = mouse_pos;
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
    char symb = '?';
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

void Fractol::Terminate(const QuitEvent&) {
    std::cout << "Application is terminating" << std::endl;
    is_running_ = false;
}

void DrawOnTheWindow(std::shared_ptr<ResourceManager> resource_manager, std::shared_ptr<Window> window, uint8_t R,
                     uint8_t G, uint8_t B) {
    if (window == nullptr) {
        return;
    }

    auto canvas = window->GetCanvas().lock();

    for (auto& pixel : *canvas) {
        pixel = 0xFF00;
    }

    for (uint64_t x = 0; x < canvas->GetWidth() / 2; x++) {
        for (uint64_t y = 0; y < canvas->GetHeight() / 2; y++) {
            canvas->At(x, y).SetColor({R, G, B});
        }
    }

    for (uint64_t x = canvas->GetWidth() / 2; x < canvas->GetWidth(); x++) {
        for (uint64_t y = canvas->GetHeight() / 2; y < canvas->GetHeight(); y++) {
            canvas->At(x, y) = 0xFF;
        }
    }

    canvas->At(100, 100).R(0x12);
    canvas->At(100, 100).G(0x34);
    canvas->At(100, 100).B(0x56);
    canvas->At(100, 100).A(0x78);

    Painter painter(window->GetCanvas());

    painter.DrawLine({0, 0}, {184, 17}, {0xFF, 0x00, 0x00});

    painter.DrawCircle({125, 125}, 50, {0xFF, 0x00, 0x00}, 10);

    painter.DrawFilledCircle({275, 95}, 50, {0x00, 0x00, 0xFF});

    painter.DrawRect({350, 375}, 100, 50, {0xFF, 0x00, 0x00}, 2);

    painter.DrawFilledRect({550, 375}, 100, 50, {0xFF, 0x00, 0x00});

    painter.DrawText({20, 500}, "Hello Katya", resource_manager->Get<FontResource>("Ubuntu24"), {0xFF, 0x00, 0x00});
}

uint8_t Fractol::Run() {
    auto window1 = windows_manager_->CreateWindow<SDLWindow>("Hello", 800, 800);
    auto window2 = windows_manager_->CreateWindow<SDLWindow>("World", 800, 800);
    DrawOnTheWindow(resource_manager_, window1.lock(), 0xF5, 0x57, 0x23);
    DrawOnTheWindow(resource_manager_, window2.lock(), 0xFF, 0xFF, 0xFF);
    while (is_running_) {
        event_handler_->Poll();
        windows_manager_->UpdateWindows();
    }
    return 0;
}

}  // namespace cozz
