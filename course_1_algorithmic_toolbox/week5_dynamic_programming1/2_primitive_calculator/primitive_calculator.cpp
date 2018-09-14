/**
 * primitive_calculator.cpp
 *
 * By Sebastian Raaphorst, 2018.
 *
 * Given a calculator with three operations (+1, *2, *3), find the fewest number of steps needed to get from 1
 * to a given number n, and the sequence of numbers resulting from the operations.
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

enum class Operation {
    PLUS1 = 1,
    TIMES2 = 2,
    TIMES3 = 3,
};

using Step  = std::pair<size_t, Operation>;
using Steps = std::vector<Step>;

std::vector<size_t> optimal_sequence(size_t n) {
    Steps calculations;
    calculations.emplace_back(std::make_pair(1, Operation::PLUS1));

    for (size_t i = 1; i <= n; ++i) {
        Steps candidates;
        candidates.emplace_back(std::make_pair(calculations[i-1].first + 1, Operation::PLUS1));
        if (i % 2 == 0)
            candidates.emplace_back(std::make_pair(calculations[i/2].first + 1, Operation::TIMES2));
        if (i % 3 == 0)
            candidates.emplace_back(std::make_pair(calculations[i/3].first + 1, Operation::TIMES3));

        const auto step = min_element(candidates.cbegin(), candidates.cend(),
                [](const auto &x, const auto &y) { return x.first < y.first; });
        calculations.emplace_back(*step);
    }

    // Now backtrack through, collecting the steps.
    std::vector<size_t> sequence;
    size_t i = n;
    while (i > 0) {
        sequence.emplace_back(i);

        switch (calculations[i].second) {
            case Operation::TIMES3:
                i /= 3;
                break;
            case Operation::TIMES2:
                i /= 2;
                break;
            case Operation::PLUS1:
                i -= 1;
                break;
        }
    }

    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() {
    size_t n;
    std::cin >> n;

    std::vector<size_t> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << '\n';
    copy(sequence.cbegin(), sequence.cend(), std::ostream_iterator<size_t>(std::cout, " "));
}
