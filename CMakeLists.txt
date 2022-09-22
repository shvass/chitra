# This file is a part of  chitra (चित्र)
# Copyright (C) 2022  akshay bansod <akshay.bnsod@gmail.com>

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

project(chitra LANGUAGES C CXX)

OPTION(USE_SYSTEM_LIBS "use system libraries rather than building from source" ON)

set(CMAKE_CXX_STANDARD 17)


file(GLOB chitra_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp)

# additional sources
list(APPEND chitra_sources

)

# additional libraries
list(APPEND libraries

)


# include the searchLib function
include(cmake/searchLib.cmake)


add_executable(chitra ${chitra_sources})
target_link_libraries(chitra ${libraries})
