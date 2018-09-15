cmake_minimum_required(VERSION 3.12)
project(data_structures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enables testing from this directory downwards.
enable_testing(true)
add_subdirectory(test)

add_subdirectory(course_1_algorithmic_toolbox)
add_subdirectory(course_2_data_structures)