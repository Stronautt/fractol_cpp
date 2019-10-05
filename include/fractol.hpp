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

#ifndef FRACTOL_INCLUDE_FRACTOL_HPP_
#define FRACTOL_INCLUDE_FRACTOL_HPP_

#include <atomic>
#include <cstdint>
#include <memory>
#include <vector>

namespace cozz {

class EventHandler;
class WindowsManager;
class MouseWheelEvent;
class MouseButtonEvent;
class MouseMotionEvent;
class KeyboardEvent;
class QuitEvent;

class Fractol final {
  public:
    Fractol(int argc, char** argv);
    ~Fractol();

    uint8_t Run();

  private:
    std::atomic<bool> is_running_;
    std::shared_ptr<EventHandler> event_handler_;
    std::shared_ptr<WindowsManager> windows_manager_;

    void MouseWheelHandler(const MouseWheelEvent& event);

    void MouseButtonHandler(const MouseButtonEvent& event);

    void MouseMotionHandler(const MouseMotionEvent& event);

    void KeyboardHandler(const KeyboardEvent& event);

    void Terminate(const QuitEvent& event);
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_FRACTOL_HPP_
