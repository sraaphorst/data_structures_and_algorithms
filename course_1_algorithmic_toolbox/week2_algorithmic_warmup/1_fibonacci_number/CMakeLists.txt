add_executable(fibonacci fibonacci.cpp)

add_executable(test_fibonacci ${TEST_SOURCES} test_fibonacci.cpp fibonacci.cpp)
target_compile_definitions(test_fibonacci PUBLIC -Dtesting=1)
target_link_libraries(test_fibonacci Catch)
