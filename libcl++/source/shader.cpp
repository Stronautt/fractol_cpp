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

#include "clpp/shader.hpp"

#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>

#include "clpp/exception.hpp"
#include "clpp/platform.hpp"

namespace cozz {

namespace clpp {

Shader::Shader(const Platform& cl_platform, const std::vector<std::string>& source_paths)
    : cl_platform_(cl_platform), device_memory_region_({nullptr, 0}) {
    if (source_paths.empty()) {
        throw cl_error("No source files were specified");
    }

    uint64_t sources_count = source_paths.size();
    auto deleter = [&sources_count](char** sources) {
        for (uint64_t i = 0; i < sources_count; ++i) {
            delete[] sources[i];
        }
        delete[] sources;
    };
    std::unique_ptr<char*, decltype(deleter)> arr(new char*[sources_count], deleter);

    std::vector<size_t> source_sizes;
    uint64_t it = 0;
    for (const auto& source_path : source_paths) {
        try {
            std::ifstream shader_stream(source_path);
            if (!shader_stream.good()) {
                throw cl_error("Can't open the shader source file");
            }

            std::streambuf* content_stream = shader_stream.rdbuf();

            const uint64_t source_size = content_stream->pubseekoff(0, shader_stream.end);
            auto& source = arr.get()[it++];

            source = new char[source_size + 1];
            content_stream->pubseekoff(0, shader_stream.beg);
            content_stream->sgetn(source, source_size + 1);
            source_sizes.push_back(source_size);
        } catch (const std::ifstream::failure& e) {
            throw cl_error("Can't open the shader source file: " + std::string(e.what()));
        }
    }

    cl_int error;
    cl_program_ = clCreateProgramWithSource(cl_platform_.GetContext(), sources_count,
                                            const_cast<const char**>(arr.get()), source_sizes.data(), &error);
    if (error) {
        throw cl_error("Can't create shader from the sources");
    }
}

Shader::~Shader() {
    if (device_memory_region_.first != nullptr) {
        clReleaseMemObject(device_memory_region_.first);
    }
    std::for_each(cl_kernels_.begin(), cl_kernels_.end(), [](const auto& kernel) { clReleaseKernel(kernel.second); });
    clReleaseProgram(cl_program_);
}

void Shader::UpdateAssociatedDevices() {
    associated_devices_.clear();

    cl_uint number_of_devices = 0;
    if (clGetProgramInfo(cl_program_, CL_PROGRAM_NUM_DEVICES, sizeof(number_of_devices), &number_of_devices, nullptr) ||
        !number_of_devices) {
        throw cl_error("Can't get number of associated to shader devices");
    }

    std::vector<cl_device_id> device_ids(number_of_devices);
    if (clGetProgramInfo(cl_program_, CL_PROGRAM_DEVICES, device_ids.size() * sizeof(cl_device_id), device_ids.data(),
                         nullptr)) {
        throw cl_error("Can't get associated to shader devices");
    }
    for (const auto& device_id : device_ids) {
        associated_devices_.push_back(cl_platform_.GetDevice(device_id));
    }
}

cl_program Shader::GetProgram() const { return cl_program_; }

void Shader::ReallocateDeviceMemoryRegion(uint64_t size) {
    if (device_memory_region_.first != nullptr && clReleaseMemObject(device_memory_region_.first)) {
        throw cl_error("Can't release device memory region");
    }
    cl_int error;
    device_memory_region_.first = clCreateBuffer(cl_platform_.GetContext(), CL_MEM_READ_WRITE, size, nullptr, &error);
    if (error) {
        throw cl_error("Can't create device memory region");
    }
}

cl_kernel Shader::GetKernel(const std::string& name) {
    try {
        return cl_kernels_.at(name);
    } catch (const std::out_of_range&) {
        cl_int error;
        cl_kernel kernel = clCreateKernel(cl_program_, name.c_str(), &error);
        if (error) {
            throw cl_error("Can't create kernel for '" + name + "()'");
        }
        return (cl_kernels_[name] = kernel);
    }
}

}  // namespace clpp

}  // namespace cozz