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



if(USE_SYSTEM_LIBS)
    find_package(PkgConfig)
endif()

# searches library in system, if not found builds from source
# searchLib(aliasName   [libraries...])
function(searchLib name)

    # try -find via package config
    if(PkgConfig_FOUND)
        pkg_check_modules(${name} ${ARGN})
    endif()
    
    # whether pkgConfig found the library
    if(${${name}_FOUND})
        # add a interface library named ${name}
        add_library(${name} INTERFACE)
        target_link_libraries(${name} INTERFACE ${${name}_LIBRARIES})
        target_include_directories(${name} INTERFACE ${${name}_INCLUDE_DIRS})
        target_link_directories(${name} INTERFACE ${${name}_LIBRARY_DIRS})
        set(${name} ${name} PARENT_SCOPE)    # export to parent scope

    else() 
        # include library specific cmake file to build from source
        include(cmake/${name}.cmake)
    endif()

    set(libraries ${libraries} ${name} PARENT_SCOPE)
endfunction(searchLib name)

