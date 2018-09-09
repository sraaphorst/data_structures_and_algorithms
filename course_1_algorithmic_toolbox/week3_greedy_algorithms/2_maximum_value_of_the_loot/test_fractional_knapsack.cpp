/**
 * test_fractional_knapsack.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <catch.hpp>

#include <vector>
using std::vector;

#include <common.h>
#include "fractional_knapsack.h"


TEST_CASE("Three items") {
    REQUIRE(get_optimal_value(50, vector<int>{20, 50, 30}, vector<int>{60, 100, 120}) == 180);
}

TEST_CASE("One item") {
    // Single arguments provided to vector indicate vector size.
    vector<int> value = {500};
    vector<int> weight = {30};
    REQUIRE(ALMOST_EQUALS(get_optimal_value(10, weight, value), 166.66667));
}

TEST_CASE("More cap than items") {
    REQUIRE(get_optimal_value(10, vector<int>{1, 2, 3}, vector<int>{30, 20, 9}) == 59);
}