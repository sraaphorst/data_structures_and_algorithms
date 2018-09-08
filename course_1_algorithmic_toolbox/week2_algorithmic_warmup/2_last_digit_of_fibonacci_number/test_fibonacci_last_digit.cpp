/**
 * test_fibonacci_last_digit.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <catch.hpp>
#include <common.h>

#include <climits>
#include <random>
#include <tuple>

#include "fibonacci_last_digit.h"

int generator() {
    std::random_device rd;
    std::mt19937 g{rd()};
    std::uniform_int_distribution elems(0, 200);
    return elems(g);
}

TEST_CASE("Both implementations return the same value") {
    RUN_TRIALS({
        const auto elem = generator();
        REQUIRE(get_fibonacci_last_digit_naive(elem) == get_fibonacci_last_digit_fast(elem));
    });
}