/**
 * test_last_digit_of_the_sum_of_fibonacci_numbers.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <catch.hpp>
#include <common.h>

#include "fibonacci_sum_last_digit.h"

TEST_CASE("Case 3") {
    REQUIRE(fibonacci_sum_fast(3) == 4);
}

TEST_CASE("Case 100") {
    REQUIRE(fibonacci_sum_fast(100) == 5);
}