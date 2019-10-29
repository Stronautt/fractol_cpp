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

#include "clpp/platform.hpp"
#include "clpp/exception.hpp"

namespace cozz {

namespace clpp {

template <class ParameterType>
void Shader::SetKernelArgument(cl_kernel kernel, uint32_t n, const ParameterType& parameter) {
    if (clSetKernelArg(kernel, n, sizeof(ParameterType), static_cast<const void*>(&parameter))) {
        throw cl_error("Can't set the kernel argument #" + std::to_string(n));
    }
}

template <class ParameterType, class... Args>
void Shader::SetKernelArgument(cl_kernel kernel, uint32_t n, const ParameterType& parameter, const Args&... args) {
    SetKernelArgument(kernel, n++, parameter);
    SetKernelArgument(kernel, n, args...);
}

template <class... Args>
void Shader::Calculate(const std::string& function, void* buffer, uint64_t buffer_size,
                           std::vector<size_t> work_size, const Args&... args) {
    uint64_t work_dimensions = work_size.size();
    if (work_dimensions > 3) {
        throw cl_error("Maximum work size dimension equal to 3, current: " + std::to_string(work_dimensions));
    }
    work_size.resize(3);
    if (!device_memory_region_.first || device_memory_region_.second != buffer_size) {
        ReallocateDeviceMemoryRegion(buffer_size);
    }
    const auto& kernel = GetKernel(function);
    SetKernelArgument(kernel, 0, device_memory_region_.first);
    SetKernelArgument(kernel, 1, args...);
    const auto& queues = cl_platform_.GetQueues(device_build_for_);
    const auto& queues_count = queues.size();

    size_t offset = 0;
    for (const auto& queue : queues) {
        std::vector<size_t> work_offset = {work_size[0] / queues_count * offset, work_size[1] / queues_count * offset,
                                           work_size[2] / queues_count * offset};
        if (clEnqueueNDRangeKernel(queue.second, kernel, work_dimensions, work_offset.data(),
                                   work_size.data(), nullptr, 0, nullptr, nullptr)) {
            throw cl_error("Can't enqueue a command to execute a kernel on a device");
        }
        ++offset;
    }
    offset = 0;
    for (const auto& queue : queues) {
        if (clEnqueueReadBuffer(queue.second, device_memory_region_.first, CL_TRUE, offset,
                                buffer_size - offset, buffer, 0, nullptr, nullptr)) {
            throw cl_error("Can't enqueue commands to read from a buffer object to host memory.");
        }
        offset += buffer_size / queues_count;
    }
}

}  // namespace clpp

}  // namespace cozz
