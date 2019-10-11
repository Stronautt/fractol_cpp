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

#ifndef LIBZZGUI_INCLUDE_CONTROLLERS_MANAGER_HPP_
#define LIBZZGUI_INCLUDE_CONTROLLERS_MANAGER_HPP_

#include <memory>
#include <vector>

namespace cozz {

namespace zzgui {

class Controller;

class ControllersManager final {
  public:
    void Push(std::shared_ptr<Controller> controller);

    void Pop();

    void Render() const;

    void Set(std::shared_ptr<Controller> controller);

    void Clear();

  private:
    std::vector<std::shared_ptr<Controller>> controllers_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_CONTROLLERS_MANAGER_HPP_
