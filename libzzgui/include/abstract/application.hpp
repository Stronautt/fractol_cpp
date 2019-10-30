/*
 * This file is part of LibZZgui.

 * LibZZgui is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZgui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZgui. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef LIBZZGUI_INCLUDE_INTERFACES_APPLICATION_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_APPLICATION_HPP_

#include <cstdint>
#include <string>

namespace cozz {

namespace zzgui {

class QuitEvent;

class Application {
  public:
    enum ExitCode : int { kSuccess = 0, kGeneralFailure, kFatalError };

    virtual ~Application();

    static float GetDeltaTime();

    virtual uint8_t Run() = 0;

    virtual void ShowInfoMessage(const std::string& message) const = 0;
    virtual void ShowErrorMessage(const std::string& message) const = 0;

    void Terminate();

  protected:
    static void UpdateDeltaTime();

    virtual void Terminate(const QuitEvent& event) = 0;

  private:
    static thread_local float delta_time_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_APPLICATION_HPP_
