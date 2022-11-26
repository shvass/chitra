# This file is a part of  chitra (चित्र)
# Copyright (C) 2022  akshay bansod <aksh.bansod@yahoo.com>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.



cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

project(chitra LANGUAGES C CXX)

OPTION(USE_SYSTEM_LIBS "use system libraries rather than building from source" ON)
OPTION(BUILD_DOCS "Generate Doxygen (html) documentation" ON)


file(GLOB chitra_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp)
# exclude tests directory from chitra source
list(FILTER chitra_sources EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/tests/")

# additional sources
list(APPEND chitra_sources

)

# additional libraries
list(APPEND libraries

)


# include the searchLib function
include(cmake/searchLib.cmake)
searchLib(ffmpeg libavcodec libavformat libavutil)
searchLib(glfw glfw3)
searchLib(glad glad)
searchLib(imgui imgui)

# setup testing, docs
include(cmake/tests.cmake)
include(cmake/genDocs.cmake)

# add chitra executable
add_executable(chitra ${chitra_sources})
target_link_libraries(chitra ${libraries})
target_include_directories(chitra PRIVATE ${CMAKE_SOURCE_DIR})
