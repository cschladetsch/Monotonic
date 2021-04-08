cmake_minimum_required (VERSION 3.9.1)
set(PROJ monotonic)
project(${PROJ})

if (WIN32)
	set(BOOST_ROOT "c:\\lib\\Boost\\boost_1_75_0")
endif(WIN32)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(libs/monotonic/test)

