/*
 * This file is part of LibZZgui.

 * LibZZgui is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZgui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZgui. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#include "clpp/shader.hpp"

#include "clpp/device.hpp"
#include "clpp/exception.hpp"
#include "clpp/platform.hpp"

namespace cozz {

namespace clpp {

template <class ParameterType>
void Shader::SetKernelArgument(cl_kernel kernel, uint32_t n, const ParameterType& parameter) {
    cl_int error;
    if ((error = clSetKernelArg(kernel, n, sizeof(ParameterType), static_cast<const void*>(&parameter)))) {
        std::string error_msg = "Can't set the kernel argument #" + std::to_string(n) + "(" +
                                std::to_string(sizeof(ParameterType)) + " bytes): ";
        switch (error) {
            case CL_INVALID_KERNEL:
                error_msg += "Invalid kernel";
                break;
            case CL_INVALID_ARG_INDEX:
                error_msg += "Invalid argument index";
                break;
            case CL_INVALID_ARG_VALUE:
                error_msg += "Invalid argument value";
                break;
            case CL_INVALID_MEM_OBJECT:
                error_msg += "Invalid memory object";
                break;
            case CL_INVALID_SAMPLER:
                error_msg += "Invalid sampler";
                break;
            case CL_INVALID_ARG_SIZE:
                error_msg += "Invalid argument size";
                break;
            default:
                error_msg += "UNKNOWN_ERROR";
                break;
        }
        throw cl_error(error_msg);
    }
}

template <class ParameterType, class... Args>
void Shader::SetKernelArgument(cl_kernel kernel, uint32_t n, const ParameterType& parameter, const Args&... args) {
    SetKernelArgument(kernel, n++, parameter);
    SetKernelArgument(kernel, n, args...);
}

template <class... Args>
void Shader::Calculate(const std::string& function, void* buffer, uint64_t buffer_size, std::vector<size_t> work_size,
                       const Args&... args) {
    uint64_t work_dimensions = work_size.size();
    if (work_dimensions > 3) {
        throw cl_error("Maximum work size dimension equal to 3, current: " + std::to_string(work_dimensions));
    }
    work_size.resize(3);
    if (!std::get<0>(device_memory_region_)
        || std::get<1>(device_memory_region_) != buffer
        || std::get<2>(device_memory_region_) != buffer_size) {
        ReallocateDeviceMemoryRegion(buffer, buffer_size);
    }
    const auto& kernel = GetKernel(function);
    SetKernelArgument(kernel, 0, std::get<0>(device_memory_region_), args...);
    if (clEnqueueNDRangeKernel(cl_device_->GetCommandQueue(), kernel, work_dimensions, nullptr,
                               work_size.data(), nullptr, 0, nullptr, nullptr)) {
        throw cl_error("Can't enqueue a command to execute a kernel on a device");
    } else if (clEnqueueReadBuffer(cl_device_->GetCommandQueue(), std::get<0>(device_memory_region_), CL_TRUE, 0,
                            buffer_size, buffer, 0, nullptr, nullptr)) {
        throw cl_error("Can't enqueue commands to read from a buffer object to host memory.");
    }
}

}  // namespace clpp

}  // namespace cozz
