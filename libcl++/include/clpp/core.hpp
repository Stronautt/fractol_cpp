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

#ifndef LIBCLPP_INCLUDE_CLPP_CORE_HPP_
#define LIBCLPP_INCLUDE_CLPP_CORE_HPP_

#include <map>
#include <memory>
#include <string>

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

namespace cozz {

namespace clpp {

class Platform;
class Shader;

class Core final {
  public:
    Core();

    std::shared_ptr<Platform> GetPlatform() const;
    std::shared_ptr<Platform> GetPlatform(const std::string& name) const;

  private:
    std::map<std::string, std::shared_ptr<Platform>> platforms_;
};

}  // namespace clpp

}  // namespace cozz

#endif  // LIBCLPP_INCLUDE_CLPP_CORE_HPP_
