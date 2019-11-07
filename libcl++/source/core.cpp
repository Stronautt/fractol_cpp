/*
 * This file is part of LibCL++.

 * LibCL++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibCL++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibCL++. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#include "clpp/core.hpp"

#include <algorithm>
#include <memory>
#include <vector>

#include "clpp/exception.hpp"
#include "clpp/platform.hpp"

namespace cozz {

namespace clpp {

Core::Core() {
    uint32_t number_of_platforms;
    if (clGetPlatformIDs(0, nullptr, &number_of_platforms)) {
        throw cl_error("Can't get number of platforms");
    }

    std::vector<cl_platform_id> platform_ids(number_of_platforms);
    if (clGetPlatformIDs(platform_ids.size(), platform_ids.data(), nullptr)) {
        throw cl_error("Can't get platform IDs");
    }

    for (const auto& platform_id : platform_ids) {
        try {
            auto platform = std::make_shared<Platform>(platform_id);
            platforms_[platform->GetName()] = platform;
        } catch (const cl_error&) {
            continue;
        }
    }
}

const std::map<std::string, std::shared_ptr<Platform>>& Core::GetPlatforms() const { return platforms_; }

std::shared_ptr<Platform> Core::GetPlatform() const {
    if (platforms_.empty()) {
        throw cl_error("No platforms were found");
    }
    return platforms_.begin()->second;
}

std::shared_ptr<Platform> Core::GetPlatform(const std::string& name) const {
    if (platforms_.empty()) {
        throw cl_error("No platforms were found");
    }
    for (const auto& platform : platforms_) {
        const auto& platform_name = platform.first;
        if (std::search(platform_name.begin(), platform_name.end(), name.begin(), name.end(),
                        [](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }) != platform_name.end()) {
            return platform.second;
        }
    }
    throw cl_error("Can't get platform with specified name: " + name);
}

}  // namespace clpp

}  // namespace cozz
