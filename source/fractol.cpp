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

#include <iostream>

#include "clpp_core.hpp"
#include "controllers/menu.hpp"
#include "controllers_manager.hpp"

namespace cozz {

Fractol::Fractol(int, char**) {
    clpp::ClppCore open_cl;
    char buffer[128];

    for (const auto& device : open_cl.GetDevices()) {
        for (const auto& id : device.second) {
            if (!clGetDeviceInfo(id, CL_DEVICE_NAME, sizeof(buffer), buffer, nullptr)) {
                std::cout << buffer << std::endl;
            }
        }
    }

    controller_manager_->Set(std::make_shared<MenuController>());
}

}  // namespace cozz
