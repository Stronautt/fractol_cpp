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
}

Device::~Device() { clReleaseCommandQueue(command_queue_); }

cl_device_id Device::GetId() const { return id_; }

cl_device_type Device::GetType() const { return type_; }

cl_command_queue Device::GetCommandQueue() const { return command_queue_; }

}  // namespace clpp

}  // namespace cozz
