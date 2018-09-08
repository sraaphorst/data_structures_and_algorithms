/**
 * test_lcm.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <catch.hpp>
#include <common.h>

#include <climits>
#include <random>
#include <tuple>

#include "lcm.h"

int generator() {
    std::random_device rd;
    std::mt19937 g{rd()};
    std::uniform_int_distribution elems(1, INT_MAX);

    // Determine number of elements.
    return elems(g);
}

TEST_CASE("Both implementations return the same value") {
    RUN_TRIALS({
        const auto a = generator();
        const auto b = generator();
        REQUIRE(lcm_naive(a, b) == lcm_fast(a, b));
    });
}
