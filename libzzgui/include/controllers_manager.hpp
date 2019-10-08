/*
 * This file is part of LibZZmvc.

 * LibZZmvc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZmvc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZmvc. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef LIBZZMVC_INCLUDE_CONTROLLERS_MANAGER_HPP_
#define LIBZZMVC_INCLUDE_CONTROLLERS_MANAGER_HPP_

#include <memory>
#include <vector>

namespace cozz {

namespace zzmvc {

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

}  // namespace zzmvc

}  // namespace cozz

#endif  // LIBZZMVC_INCLUDE_CONTROLLERS_MANAGER_HPP_
