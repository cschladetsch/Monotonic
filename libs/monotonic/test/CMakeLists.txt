cmake_minimum_required (VERSION 2.8.11)

set(SOURCE_FILES compare_memory_pool.cpp)

add_executable(${PROJ} ${SOURCE_FILES})

target_include_directories(${PROJ} PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(${PROJ} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
