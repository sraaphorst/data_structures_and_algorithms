add_executable(fibonacci fibonacci.cpp ../7_last_digit_of_the_sum_of_fibonacci_numbers_again/fibonacci_partial_sum.h ../7_last_digit_of_the_sum_of_fibonacci_numbers_again/test_fibonacci_partial_sum.cpp)

add_executable(test_fibonacci ${TEST_SOURCES} test_fibonacci.cpp fibonacci.cpp)
target_compile_definitions(test_fibonacci PUBLIC -Dtesting=1)
target_link_libraries(test_fibonacci Catch)
