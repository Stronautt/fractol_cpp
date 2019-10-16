##
 # This file is part of LibZZgui.

 # LibZZgui is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # LibZZgui is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with LibZZgui. If not, see <https://www.gnu.org/licenses/>.
 #
 # Author: Pavlo Hrytsenko
##

cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(zzgui VERSION 0.1.0 LANGUAGES CXX)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wextra -Wall -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Werror -fsanitize=leak")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s")

set(LIB_NAME ${PROJECT_NAME} CACHE STRING "Name of the library" FORCE)

add_library(${LIB_NAME} STATIC source/event/event.cpp
                               source/event/window_moved_event.cpp
                               source/event/window_resized_event.cpp
                               source/event/keyboard_event.cpp
                               source/event/mouse_motion_event.cpp
                               source/event/mouse_button_event.cpp
                               source/event/mouse_wheel_event.cpp
                               source/event/quit_event.cpp
                               source/event_handler.cpp
                               source/sdl_utilities.cpp
                               source/sdl_event_handler.cpp
                               source/canvas.cpp
                               source/window.cpp
                               source/sdl_window.cpp
                               source/windows_manager.cpp
                               source/painter.cpp
                               source/resource.cpp
                               source/resource_manager.cpp
                               source/font_resource.cpp
                               source/model.cpp
                               source/view.cpp
                               source/controller.cpp
                               source/controllers_manager.cpp
                               source/application.cpp
                               source/sdl_application.cpp)
target_include_directories(${LIB_NAME} PUBLIC include
                                              include/interfaces
                                       PRIVATE source/include
                                               ${SDL2_INCLUDE_DIRS})
target_link_libraries(${LIB_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2_ttf)
