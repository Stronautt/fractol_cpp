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
#include <chrono>
#include <ctime>
#include <fstream>
#include <memory>
#include <sstream>

#include "clpp/exception.hpp"
#include "clpp/platform.hpp"

namespace cozz {

namespace clpp {

Shader::Shader(const Platform& cl_platform, const std::vector<std::string>& source_paths)
    : cl_platform_(cl_platform), device_memory_region_({nullptr, nullptr, 0}) {
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
    if (std::get<0>(device_memory_region_) != nullptr) {
        clReleaseMemObject(std::get<0>(device_memory_region_));
    }
    std::for_each(cl_kernels_.begin(), cl_kernels_.end(), [](const auto& kernel) { clReleaseKernel(kernel.second); });
    clReleaseProgram(cl_program_);
}

void Shader::Build(std::shared_ptr<const Device> device, const std::string& build_options) {
    if (!device) {
        throw cl_error("Can't build. Bad device");
    }

    cl_device_id device_id = device->GetId();
    if (clBuildProgram(cl_program_, 1, &device_id, build_options.c_str(), nullptr, nullptr)) {
        size_t build_log_len;
        if (clGetProgramBuildInfo(cl_program_, device_id, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_len)) {
            throw cl_error("Can't get shader build log length");
        }
        std::unique_ptr<char[]> build_log(new char[build_log_len]);
        if (clGetProgramBuildInfo(cl_program_, device_id, CL_PROGRAM_BUILD_LOG, build_log_len, build_log.get(), nullptr)) {
            throw cl_error("Can't get shader build log");
        }
        std::ofstream build_log_file("cl_build_error.log", std::fstream::out | std::fstream::app);
        std::time_t time_point = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        build_log_file << "BUILD ERROR: " << std::ctime(&time_point) << build_log.get() << std::endl;

        throw cl_error("Can't build the shader. See 'cl_build_error.log' for details");
    }
    cl_device_ = device;
}

cl_program Shader::GetProgram() const { return cl_program_; }

void Shader::ReallocateDeviceMemoryRegion(void* buffer, uint64_t size) {
    if (std::get<0>(device_memory_region_) != nullptr && clReleaseMemObject(std::get<0>(device_memory_region_))) {
        throw cl_error("Can't release device memory region");
    }
    cl_int error;
    std::get<0>(device_memory_region_) = clCreateBuffer(cl_platform_.GetContext(), CL_MEM_USE_HOST_PTR, size, buffer, &error);
    std::get<1>(device_memory_region_) = buffer;
    std::get<2>(device_memory_region_) = size;
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
