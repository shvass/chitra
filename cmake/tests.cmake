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


# testing configuration file
# each cpp file in tests directory is a test
# hpp files are ignored

include(CTest)
file(GLOB testSrcs ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

# use chitra sources except main
list(APPEND additionalSrcs ${chitra_sources})
list(FILTER additionalSrcs EXCLUDE REGEX "chitra.cpp")

foreach(src ${testSrcs})
    # extract textName
    cmake_path(RELATIVE_PATH src BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests OUTPUT_VARIABLE testName)
    cmake_path(REMOVE_EXTENSION testName)

    # test build configuration
    add_executable(${testName} ${src} ${additionalSrcs})
    target_link_libraries(${testName} ${libraries})
    target_include_directories(${testName} PUBLIC ${CMAKE_SOURCE_DIR})
    set_target_properties(${testName} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"  #output all test binaries to tests dir
    )

    add_test(NAME ${testName} 
        COMMAND ${testName}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )

endforeach(src ${testSrcs})
