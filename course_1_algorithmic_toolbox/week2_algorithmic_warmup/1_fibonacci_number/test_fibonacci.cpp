/**
 * test_fibonacci.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <catch.hpp>
#include <common.h>

#include <random>

#include "fibonacci.h"

TEST_CASE("Both implementations return the same value") {
    for (size_t i = 0; i < 45; ++i)
        REQUIRE(fibonacci_fast(i) == fibonacci_naive(i));
}