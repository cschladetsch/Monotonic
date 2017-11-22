cmake_minimum_required (VERSION 2.8.11)
set(PROJ monotonic_test)
project (${PROJ})
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
find_package(BOOST)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(libs/Monotonic/test)



