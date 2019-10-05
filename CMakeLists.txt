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

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fsanitize=leak -Wextra -Werror -Wall -pedantic")

set(EXE_NAME ${PROJECT_NAME} CACHE STRING "Name of the executable")
set(LIB_NAME ${EXE_NAME}_core CACHE STRING "Name of the core library")

add_library(${LIB_NAME} STATIC source/fractol.cpp
							   source/event/event.cpp
	                           source/event/window_moved_event.cpp
	                           source/event/window_resized_event.cpp
	                           source/event/keyboard_event.cpp
	                           source/event/mouse_motion_event.cpp
	                           source/event/mouse_button_event.cpp
	                           source/event/mouse_wheel_event.cpp
	                           source/event/quit_event.cpp
	                           source/event_handler.cpp
	                           source/sdl_event_handler.cpp
	                           source/canvas.cpp
	                           source/window.cpp
	                           source/sdl_window.cpp
	                           source/windows_manager.cpp
	                           source/painter.cpp)
target_include_directories(${LIB_NAME} PUBLIC include
                                              include/interface
                                       PRIVATE source/include
                                       		   ${SDL2_INCLUDE_DIRS})

add_executable(${EXE_NAME} source/main.cpp)
target_link_libraries(${EXE_NAME} PRIVATE ${LIB_NAME} ${SDL2_LIBRARIES})
