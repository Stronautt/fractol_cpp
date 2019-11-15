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

#include "clpp/core.hpp"
#include "clpp/exception.hpp"
#include "controllers/menu.hpp"
#include "controllers_manager.hpp"

namespace cozz {

Fractol::Fractol(int, char**) {
    try {
        auto open_cl = std::make_shared<clpp::Core>();

        controller_manager_->Set(std::make_shared<MenuController>(*this, open_cl));
    } catch (const clpp::cl_error&) {
        controller_manager_->Set(std::make_shared<MenuController>(*this, nullptr));
    } catch (const std::exception& e) {
        ShowErrorMessage(e.what());
        Terminate();
    }
}

}  // namespace cozz
