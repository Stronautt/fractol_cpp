

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

#ifndef LIBCLPP_INCLUDE_CLPP_PLATFORM_HPP_
#define LIBCLPP_INCLUDE_CLPP_PLATFORM_HPP_

#include <map>
#include <memory>
#include <string>
#include <vector>

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

namespace cozz {

namespace clpp {

class Shader;
class Device;

class Platform final {
  public:
    Platform(cl_platform_id id);
    ~Platform();

    const std::string& GetName() const;

    const cl_context& GetContext() const;

    const std::map<cl_device_type, std::shared_ptr<Device>>& GetDevices() const;

    std::shared_ptr<Device> GetDevice(cl_device_id search_device_id) const;

    std::shared_ptr<Shader> LoadShader(const std::vector<std::string>& source_paths) const;
  private:
    cl_platform_id id_;
    std::string name_;

    cl_context context_;

    std::map<cl_device_type, std::shared_ptr<Device>> devices_;

    void ExtractInfo();
};

}  // namespace clpp

}  // namespace cozz

#endif  // LIBCLPP_INCLUDE_CLPP_PLATFORM_HPP_
