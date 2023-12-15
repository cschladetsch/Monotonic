cmake_minimum_required (VERSION 3.9.1)

set(BOOST_ROOT "/c/boost/boost_1_84_0")
find_package(Boost 1.84 REQUIRED)

set(PROJ monotonic)
project(${PROJ})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(libs/monotonic/test)

