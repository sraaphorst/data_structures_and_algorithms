add_executable(fractional_knapsack fractional_knapsack.cpp test_fractional_knapsack.cpp fractional_knapsack.h)
target_compile_definitions(fractional_knapsack PUBLIC -Dtesting=0)

add_executable(test_fractional_knapsack ${TEST_SOURCES} test_fractional_knapsack.cpp fractional_knapsack.cpp)
target_compile_definitions(test_fractional_knapsack PUBLIC -Dtesting=1)
target_link_libraries(test_fractional_knapsack Catch)
