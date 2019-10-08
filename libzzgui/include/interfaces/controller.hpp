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

#ifndef LIBZZMVC_INCLUDE_INTERFACES_CONTROLLER_HPP_
#define LIBZZMVC_INCLUDE_INTERFACES_CONTROLLER_HPP_

namespace cozz {

namespace zzmvc {

class Controller {
  public:
    virtual ~Controller() = default;

    virtual void Render() = 0;
};

}  // namespace zzmvc

}  // namespace cozz

#endif  // LIBZZMVC_INCLUDE_INTERFACES_CONTROLLER_HPP_
