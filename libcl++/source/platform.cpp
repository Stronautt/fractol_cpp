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
#include <chrono>
#include <ctime>
#include <fstream>
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

const std::map<cl_device_type, std::shared_ptr<Device>>& Platform::GetDevices() const { return devices_; }

std::shared_ptr<Device> Platform::GetDevice(cl_device_id search_device_id) const {
    for (const auto& device : devices_) {
        const auto& device_ptr = device.second;
        const auto& device_id = device_ptr->GetId();

        if (device_id == search_device_id) {
            return device_ptr;
        }
    }
    throw cl_error("No devices found with specified id");
}

std::shared_ptr<Shader> Platform::LoadShader(const std::vector<std::string>& source_paths) const {
    return std::make_shared<Shader>(*this, source_paths);
}

void Platform::BuildShader(std::shared_ptr<Shader> shader, const std::string& build_options) const {
    if (!shader) {
        throw cl_error("Can't build bad shader");
    }

    const auto& program = shader->GetProgram();

    if (clBuildProgram(program, 0, nullptr, build_options.c_str(), nullptr, nullptr)) {
        cl_device_id device_id;
        if (clGetProgramInfo(program, CL_PROGRAM_DEVICES, sizeof(device_id), &device_id, nullptr)) {
            throw cl_error("Can't get associated to shader device");
        }

        size_t build_log_len;
        if (clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_len)) {
            throw cl_error("Can't get shader build log length");
        }
        std::unique_ptr<char[]> build_log(new char[build_log_len]);
        if (clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, build_log_len, build_log.get(), nullptr)) {
            throw cl_error("Can't get shader build log");
        }
        std::ofstream build_log_file("error.log", std::fstream::out | std::fstream::app);
        std::time_t time_point = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        build_log_file << "BUILD ERROR: " << std::ctime(&time_point) << build_log.get() << std::endl;

        throw cl_error("Can't build the shader. See 'error.log' for details.");
    }

    shader->UpdateAssociatedDevices();
}

}  // namespace clpp

}  // namespace cozz
