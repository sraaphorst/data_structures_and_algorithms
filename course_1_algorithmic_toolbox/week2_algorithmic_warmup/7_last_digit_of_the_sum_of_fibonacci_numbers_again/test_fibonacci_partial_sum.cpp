/**
 * test_fibonacci_partial_sum.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <catch.hpp>

#include "fibonacci_partial_sum.h"

TEST_CASE("Case 10 200") {
    REQUIRE(get_fibonacci_partial_sum_fast(10, 200) == 2);
}

TEST_CASE("Case 3 7") {
    REQUIRE(get_fibonacci_partial_sum_fast(3, 7) == 1);
}

TEST_CASE("Case 10 10") {
    REQUIRE(get_fibonacci_partial_sum_fast(10, 10) == 5);
}