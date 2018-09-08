/**
 * test_gcd.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <catch.hpp>
#include <common.h>

#include <climits>
#include <random>
#include <tuple>

#include "gcd.h"

int generator() {
    std::random_device rd;
    std::mt19937 g{rd()};
    std::uniform_int_distribution elems(1, INT_MAX);

    // Determine number of elements.
    return elems(g);
}

TEST_CASE("Both implementations return the same value") {
    RUN_TRIALS({
        // I tried generating a pair here, but the compiler would have none of it.
        const auto a = generator();
        const auto b = generator();
        REQUIRE(gcd_naive(a, b) == gcd_euclidean(a, b));
    });
}
