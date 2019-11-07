

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

#ifndef LIBCLPP_INCLUDE_CLPP_DEVICE_HPP_
#define LIBCLPP_INCLUDE_CLPP_DEVICE_HPP_

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

namespace cozz {

namespace clpp {

class Device final {
  public:
    Device(cl_context context, cl_device_id id);
    ~Device();

    cl_device_id GetId() const;

    cl_device_type GetType() const;

    cl_command_queue GetCommandQueue() const;

  private:
    cl_device_id id_;

    cl_device_type type_;

    cl_command_queue command_queue_;
};

}  // namespace clpp

}  // namespace cozz

#endif  // LIBCLPP_INCLUDE_CLPP_DEVICE_HPP_
