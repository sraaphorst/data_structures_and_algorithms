add_executable(lcm lcm.cpp)

add_executable(test_lcm ${TEST_SOURCES} test_lcm.cpp lcm.cpp)
target_compile_definitions(test_lcm PUBLIC -Dtesting=1)
target_link_libraries(test_lcm Catch)
