cmake_minimum_required (VERSION 3.9.1)
set(PROJ monotonic)
project (${PROJ})
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(libs/monotonic/test)



