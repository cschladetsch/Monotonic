cmake_minimum_required (VERSION 2.8.11)

set(PROJ_TESTS ${PROJ}_tests)

# CMake can't find boost without some help, as there's no standard places for it to look for installed 3rd party libraries
if (WIN32)
    set(BOOST_ROOT "c:\\Boost\\boost_1_73_0")
endif(WIN32)


add_executable(${PROJ} compare_memory_pool)
add_executable(${PROJ_TESTS} tests.cpp)

target_include_directories(${PROJ} PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(${PROJ} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJ_TESTS} PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(${PROJ_TESTS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
