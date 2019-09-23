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

set(EXE_NAME ${PROJECT_NAME} CACHE STRING "Name of the executable")
set(LIB_NAME ${EXE_NAME}_core CACHE STRING "Name of the the core library")

add_library(${LIB_NAME} STATIC source/fractol.cpp)
target_include_directories(${LIB_NAME} PUBLIC include
	                                   PRIVATE source/include)

add_executable(${EXE_NAME} source/main.cpp)
target_link_libraries(${EXE_NAME} PRIVATE ${LIB_NAME})
