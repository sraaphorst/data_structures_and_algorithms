add_executable(fibonacci_huge fibonacci_huge.cpp)

add_executable(test_fibonacci_huge ${TEST_SOURCES} test_fibonacci_huge.cpp fibonacci_huge.cpp)
target_compile_definitions(test_fibonacci_huge PUBLIC -Dtesting=1)
target_link_libraries(test_fibonacci_huge Catch)
