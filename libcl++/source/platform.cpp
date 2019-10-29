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

#include "clpp/exception.hpp"
#include "clpp/shader.hpp"

namespace cozz {

namespace clpp {

Platform::Platform(cl_platform_id id) : id_(id) {
    char platform_name[256];

    if (clGetPlatformInfo(id_, CL_PLATFORM_NAME, sizeof(platform_name), platform_name, nullptr)) {
        throw cl_error("Can't get platform name");
    }
    name_ = platform_name;

    QueryDevices(CL_DEVICE_TYPE_CPU);
    QueryDevices(CL_DEVICE_TYPE_GPU);
    QueryDevices(CL_DEVICE_TYPE_ACCELERATOR);

    std::vector<cl_device_id> all_device_ids;
    for (const auto& device : devices_) {
        all_device_ids.insert(all_device_ids.end(), device.second.begin(), device.second.end());
    }

    int32_t error;
    context_ = clCreateContext(nullptr, all_device_ids.size(), all_device_ids.data(), nullptr, nullptr, &error);
    if (error) {
        throw cl_error("Can't create context");
    }

    for (const auto& device : devices_) {
        const auto& type = device.first;
        const auto& ids = device.second;

        for (const auto& id : ids) {
            cl_command_queue queue = clCreateCommandQueue(context_, id, 0, &error);
            if (error) {
                continue;
            }
            queues_[type].emplace(std::make_pair(id, queue));
        }
    }
}

Platform::~Platform() {
    for (const auto& queue : queues_) {
        for (const auto& command_queue : queue.second) {
            clReleaseCommandQueue(command_queue.second);
        }
    }
    clReleaseContext(context_);
}

const std::string& Platform::GetName() const { return name_; }

const cl_context& Platform::GetContext() const { return context_; }

const std::map<cl_device_id, cl_command_queue>& Platform::GetQueues(cl_device_type device) const {
    try {
        return queues_.at(device);
    } catch (const std::out_of_range&) {
        throw cl_error("No queues with specified device type found");
    }
}

std::shared_ptr<Shader> Platform::LoadShader(const std::vector<std::string>& source_paths) const {
    return std::make_shared<Shader>(*this, source_paths);
}

void Platform::QueryDevices(cl_device_type device_type) {
    uint32_t number_of_devices;
    if (clGetDeviceIDs(id_, device_type, 0, nullptr, &number_of_devices) || !number_of_devices) {
        return;
    }
    std::vector<cl_device_id> device_ids(number_of_devices);
    if (clGetDeviceIDs(id_, device_type, device_ids.size(), device_ids.data(), NULL) || device_ids.empty()) {
        return;
    }
    try {
        devices_.at(device_type).insert(devices_.at(device_type).end(), device_ids.begin(), device_ids.end());
    } catch (const std::out_of_range&) {
        devices_.emplace(std::make_pair(device_type, std::move(device_ids)));
    }
}

}  // namespace clpp

}  // namespace cozz
