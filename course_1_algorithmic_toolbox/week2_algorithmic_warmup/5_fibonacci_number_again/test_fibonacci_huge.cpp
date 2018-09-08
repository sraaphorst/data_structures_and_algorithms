/**
 * test_fibonacci_huge.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <catch.hpp>
#include <common.h>

#include <climits>
#include <random>
#include <tuple>

#include "fibonacci_huge.h"

TEST_CASE("Case n=10 m=2") {
    REQUIRE(get_fibonacci_huge_fast(10, 2) == 1);
}

TEST_CASE("Case n=239, m=1000") {
    REQUIRE(get_fibonacci_huge_fast(239, 1000) == 161);
}

TEST_CASE("Case m=2816213588 n=239") {
    REQUIRE(get_fibonacci_huge_fast(2816213588, 239) == 151);
}
