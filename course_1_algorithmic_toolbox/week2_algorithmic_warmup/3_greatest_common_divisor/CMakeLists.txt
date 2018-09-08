add_executable(gcd gcd.cpp)

add_executable(test_gcd ${TEST_SOURCES} test_gcd.cpp gcd.cpp)
target_compile_definitions(test_gcd PUBLIC -Dtesting=1)
target_link_libraries(test_gcd Catch)
