cmake_minimum_required (VERSION 3.9.1)

set(BOOST_ROOT "/c/boost/boost_1_84_0")
set(PROJ monotonic)

project(${PROJ})

find_package(Boost)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH}")
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(libs/monotonic/test)

