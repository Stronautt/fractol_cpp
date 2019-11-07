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

#include "clpp/platform.hpp"

#include <algorithm>
#include <memory>
#include <vector>

#include "clpp/device.hpp"
#include "clpp/exception.hpp"
#include "clpp/shader.hpp"

namespace cozz {

namespace clpp {

Platform::Platform(cl_platform_id id) : id_(id) {
    char platform_name[256];

    if (clGetPlatformInfo(id_, CL_PLATFORM_NAME, sizeof(platform_name) - 1, platform_name, nullptr)) {
        throw cl_error("Can't get platform name");
    }
    name_ = platform_name;

    uint32_t number_of_devices;
    if (clGetDeviceIDs(id_, CL_DEVICE_TYPE_ALL, 0, nullptr, &number_of_devices) || !number_of_devices) {
        throw cl_error("Platform `" + name_ + "` has no devices");
    }
    std::vector<cl_device_id> device_ids(number_of_devices);
    if (clGetDeviceIDs(id_, CL_DEVICE_TYPE_ALL, device_ids.size(), device_ids.data(), NULL) || device_ids.empty()) {
        throw cl_error("Can't get device IDs from the platform `" + name_ + "`");
    }

    cl_int error = 0;
    context_ = clCreateContext(nullptr, device_ids.size(), device_ids.data(), nullptr, nullptr, &error);
    if (error) {
        throw cl_error("Can't create context for `" + name_ + "` platform");
    }

    for (const auto& id : device_ids) {
        std::shared_ptr<Device> device;
        try {
            device = std::make_shared<Device>(context_, id);
        } catch (const std::exception&) {
            continue;
        }
        devices_.emplace(std::make_pair(device->GetType(), device));
    }
}

Platform::~Platform() { clReleaseContext(context_); }

const std::string& Platform::GetName() const { return name_; }

const cl_context& Platform::GetContext() const { return context_; }

std::vector<std::shared_ptr<Device>> Platform::GetDevices(cl_device_type queried_device_type) const {
    std::vector<std::shared_ptr<Device>> ret;

    for (auto device : devices_) {
        const auto& device_type = device.first;
        const auto& device_ptr = device.second;

        if (device_type & queried_device_type) {
            ret.push_back(device_ptr);
        }
    }
    return std::move(ret);
}

std::shared_ptr<Shader> Platform::LoadShader(const std::vector<std::string>& source_paths) const {
    return std::make_shared<Shader>(*this, source_paths);
}

}  // namespace clpp

}  // namespace cozz
