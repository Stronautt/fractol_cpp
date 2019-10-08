##
 # This file is part of Fractol.

 # Fractol is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # Fractol is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with Fractol. If not, see <https://www.gnu.org/licenses/>.
 #
 # Author: Pavlo Hrytsenko
##

cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(fractol VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wextra -Wall -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Werror -fsanitize=leak")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ggdb")

set(EXE_NAME ${PROJECT_NAME} CACHE STRING "Name of the executable" FORCE)
set(LIB_NAME ${EXE_NAME}_core CACHE STRING "Name of the core library" FORCE)

add_library(${LIB_NAME} STATIC source/fractol.cpp)
target_include_directories(${LIB_NAME} PUBLIC include
                                              include/interface
                                       PRIVATE source/include)
target_link_libraries(${LIB_NAME} PUBLIC zzgraph)

add_executable(${EXE_NAME} source/main.cpp)
target_link_libraries(${EXE_NAME} PRIVATE ${LIB_NAME})

add_subdirectory(libzzgraph)
