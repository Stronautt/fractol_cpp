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

#include "clpp/device.hpp"

#include <vector>

#include "clpp/exception.hpp"

namespace cozz {

namespace clpp {

Device::Device(cl_context context, cl_device_id id) : id_(id) {
    if (clGetDeviceInfo(id_, CL_DEVICE_TYPE, sizeof(type_), &type_, nullptr)) {
        throw cl_error("Can't get device type");
    }
    cl_int error = 0;
    command_queue_ = clCreateCommandQueue(context, id, 0, &error);
    if (error) {
        throw cl_error("Can't create commnad queue");
    }

    name_ = GetStringValue(CL_DEVICE_NAME);

    if (clGetDeviceInfo(id_, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_clock_frequency_), &max_clock_frequency_,
                        nullptr)) {
        throw cl_error("Can't get device max clock frequency");
    } else if (clGetDeviceInfo(id_, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(max_compute_units_), &max_compute_units_,
                               nullptr)) {
        throw cl_error("Can't get device max compute units");
    } else if (clGetDeviceInfo(id_, CL_DEVICE_MAX_SAMPLERS, sizeof(max_samplers_), &max_samplers_, nullptr)) {
        throw cl_error("Can't get device max samplers count");
    } else if (clGetDeviceInfo(id_, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(max_memory_alloc_size_),
                               &max_memory_alloc_size_, nullptr)) {
        throw cl_error("Can't get device max memroy allocation size");
    } else if (clGetDeviceInfo(id_, CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(max_parameter_size_), &max_parameter_size_,
                               nullptr)) {
        throw cl_error("Can't get device max parameter size");
    }

    vendor_ = GetStringValue(CL_DEVICE_VENDOR);
    device_version_ = GetStringValue(CL_DEVICE_VERSION);
    driver_version_ = GetStringValue(CL_DRIVER_VERSION);
}

Device::~Device() { clReleaseCommandQueue(command_queue_); }

cl_device_id Device::GetId() const { return id_; }

cl_device_type Device::GetType() const { return type_; }

cl_command_queue Device::GetCommandQueue() const { return command_queue_; }

const std::string& Device::GetName() const { return name_; }

bool Device::IsAvailable() const {
    cl_bool available;
    if (clGetDeviceInfo(id_, CL_DEVICE_AVAILABLE, sizeof(available), &available, nullptr)) {
        throw cl_error("Can't get device availability");
    }
    return available;
}

cl_int Device::GetMaxClockFrequency() const { return max_clock_frequency_; }

cl_int Device::GetMaxComputeUnits() const { return max_compute_units_; }

cl_int Device::GetMaxSamplers() const { return max_samplers_; }

cl_ulong Device::GetMaxMemoryAllocSize() const { return max_memory_alloc_size_; }

size_t Device::GetMaxParameterSize() const { return max_parameter_size_; }

const std::string& Device::GetVendor() const { return vendor_; }

const std::string& Device::GetDeviceVersion() const { return device_version_; }

const std::string& Device::GetDriverVersion() const { return driver_version_; }

std::string Device::GetStringValue(cl_device_info type, uint64_t size) const {
    std::vector<char> value(size);
    if (clGetDeviceInfo(id_, type, value.size() - 1, value.data(), nullptr)) {
        throw cl_error("Can't get string value from the device");
    }
    return value.data();
}

}  // namespace clpp

}  // namespace cozz
