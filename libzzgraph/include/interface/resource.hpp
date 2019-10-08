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

#ifndef FRACTOL_INCLUDE_INTERFACE_RESOURCE_HPP_
#define FRACTOL_INCLUDE_INTERFACE_RESOURCE_HPP_

#include <string>

namespace cozz {

class Resource {
  public:
    Resource() = delete;

    virtual ~Resource();

    virtual const std::string& GetName() const;

  protected:
    std::string name_;

    Resource(const std::string& name);
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_INTERFACE_RESOURCE_HPP_
