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


# build config file for glfw dependency

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "disable GLFW example programs build")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "disable GLFW test build")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "disable GLFW docs build")
set(GLFW_INSTALL OFF CACHE BOOL "disable GLFW install script build")

add_subdirectory(deps/glfw)
