#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>

#ifdef testing
#include "max_pairwise_product.h"
#endif

using C = std::vector<int64_t>;

/// This is the super-safe algorithm.
int64_t MaxPairwiseProductSafe(std::vector<int> numbers) {
    auto iter = std::max_element(std::begin(numbers), std::end(numbers));
    int64_t val1 = *iter;
    numbers.erase(iter);
    auto iter2 = std::max_element(std::begin(numbers), std::end(numbers));
    int64_t val2 = *iter2;
    return val1 * val2;
}

int64_t MaxPairwiseProduct(const std::vector<int> &numbers) {
    size_t highest_idx = 0;
    size_t next_highest_idx = 0;
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] > numbers[highest_idx]) {
            next_highest_idx = highest_idx;
            highest_idx = i;
        } else if (numbers[i] > numbers[next_highest_idx] || highest_idx == next_highest_idx) {
            next_highest_idx = i;
        }
    }
    int64_t res = ((int64_t) numbers[highest_idx]) * ((int64_t) numbers[next_highest_idx]);
    return res;
}

#ifndef testing
int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    int64_t result = MaxPairwiseProduct(numbers);
    std::cout << result << "\n";
    return 0;
}
#endif