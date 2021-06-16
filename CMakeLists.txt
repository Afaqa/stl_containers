cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_compile_options(-g -Wall -Wextra)
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(ft_containers gtest.cpp)
target_link_libraries(ft_containers gtest gtest_main)
