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

#include "sdl_application.hpp"

namespace cozz {

class Fractol final : public zzgui::SdlApplication {
  public:
    Fractol(int argc, char** argv);
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_FRACTOL_HPP_
