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

#include "clpp_core.hpp"

#include <memory>
#include <vector>

#include "clpp_exception.hpp"

namespace cozz {

namespace clpp {

ClppCore::ClppCore() {
    uint32_t number_of_platforms;

    if (clGetPlatformIDs(0, nullptr, &number_of_platforms)) {
        throw cl_error("Can't get number of platforms");
    }
    std::vector<cl_platform_id> platform_ids(number_of_platforms);
    if (clGetPlatformIDs(platform_ids.size(), platform_ids.data(), nullptr)) {
        throw cl_error("Can't get platform IDs");
    }
    for (uint32_t it = 0; it < number_of_platforms; ++it) {
        QueryDevices(platform_ids[it], CL_DEVICE_TYPE_CPU);
        QueryDevices(platform_ids[it], CL_DEVICE_TYPE_GPU);
        QueryDevices(platform_ids[it], CL_DEVICE_TYPE_ACCELERATOR);
    }

    std::vector<cl_device_id> all_device_ids;
    for (const auto& device : devices_) {
        all_device_ids.insert(all_device_ids.end(), device.second.begin(), device.second.end());
    }

    int32_t error;
    context_ = clCreateContext(nullptr, all_device_ids.size(), all_device_ids.data(), nullptr, nullptr, &error);
    if (error) {
        throw cl_error("Can't create context");
    }

    for (const auto& device_id : all_device_ids) {
        cl_command_queue queue = clCreateCommandQueue(context_, device_id, 0, &error);
        if (error) {
            continue;
        }
        queues_.emplace(std::make_pair(device_id, queue));
    }
}

ClppCore::~ClppCore() {
    for (const auto& queue : queues_) {
        clReleaseCommandQueue(queue.second);
    }
    clReleaseContext(context_);
}

const std::map<cl_device_type, std::vector<cl_device_id>>& ClppCore::GetDevices() const { return devices_; }

void ClppCore::QueryDevices(cl_platform_id platform_id, cl_device_type device_type) {
    uint32_t number_of_devices;

    if (clGetDeviceIDs(platform_id, device_type, 0, nullptr, &number_of_devices) || !number_of_devices) {
        return;
    }
    std::vector<cl_device_id> device_ids(number_of_devices);
    if (clGetDeviceIDs(platform_id, device_type, device_ids.size(), device_ids.data(), NULL) || device_ids.empty()) {
        return;
    }
    devices_[device_type] = std::move(device_ids);
}

}  // namespace clpp

}  // namespace cozz
