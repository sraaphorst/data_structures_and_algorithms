#include <algorithm>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>
using std::vector;

#if (defined(testing) && (testing == 1))
#include "fractional_knapsack.h"
#endif

double get_optimal_value(int capacity, const vector<int> &weights, const vector<int> &values) {
    double value = 0.0;

    // We want value / weight for each item, to determine the most valuable things we can take.
    vector<std::pair<size_t, double>> val_per_wt;
    for (size_t idx = 0; idx < weights.size(); ++idx)
        val_per_wt.emplace_back(std::make_pair(idx, ((double) values[idx]) / weights[idx]));

    // We want more valuable objects at the back so that we can pop them off.
    std::sort(std::begin(val_per_wt), std::end(val_per_wt), [](const auto vw1, const auto vw2) { return vw1.second < vw2.second;});

    // Now keep taking as much as we can from the last item and pop if we take it all.
    while (capacity > 0 && !val_per_wt.empty()) {
        // Two cases: we take all of the last item, or can only take some of it.
        // The compiler over at the grading page doesn't allow tuple decomposition.
        const auto &item = val_per_wt.back();
        const auto cur_idx = item.first;
        const auto cur_vpw = item.second;

        if (weights[cur_idx] <= capacity) {
            value    += values[cur_idx];
            capacity -= weights[cur_idx];
            val_per_wt.pop_back();
        } else {
            value += capacity * cur_vpw;
            capacity = 0;
        }
    }

    return value;
}

#if (!defined(testing) || (testing == 0))
int main() {
    int n;
    int capacity;
    std::cin >> n >> capacity;
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}
#endif