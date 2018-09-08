/**
 * test_max_pairwise_product.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

/**
 * A stress test comprises:
 * 1. Your implementation of an algorithm.
 * 2. An alternative, trivial and slow, but correct implementation of an algorithm for the same problem.
 * 3. A random test generator.
 * 4. An infinite loop that compares the results and stops if the outputs differ.
 */

#include <catch.hpp>
#include <common.h>

#include <random>
#include <vector>

#include "max_pairwise_product.h"

const std::vector<int> generator() {
    std::random_device rd;
    std::mt19937 g{rd()};
    std::uniform_int_distribution size(2, 100000);
    std::uniform_int_distribution elems(0, 20000);

    // Determine number of elements.
    int num = size(g);
    std::vector<int> input{num};
    for (auto i=0; i < num; ++i)
        input.emplace_back(elems(g));
    return input;
}

TEST_CASE("Both implementations return the same product") {
    RUN_TRIALS({
        const std::vector<int> c = generator();
        REQUIRE(MaxPairwiseProductSafe(c) == MaxPairwiseProduct(c));
    });
}