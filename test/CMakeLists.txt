project(Catch VERSION 0.1.0 LANGUAGES CXX)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE")
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

# Make test executable
set(TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" PARENT_SCOPE)
add_executable(tests main.cpp)
target_link_libraries(tests Catch)

