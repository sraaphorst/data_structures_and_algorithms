#include <iostream>
#include <vector>
using std::vector;

#if (testing == 1)
#include "fibonacci_partial_sum.h"
#endif

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

// Formulate the Pisano sequence, i.e. the fibonacci numbers mod 10, which has period 60.
struct Digits {
    std::vector<int> digits{60};
    Digits() {
        digits[0] = 0;
        digits[1] = 1;
        for (int i = 2; i < 60; ++i)
            digits[i] = (digits[i - 1] + digits[i - 2]) % 10;
    }
};

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    // The sum of all up to b is F(b+2) - 1.
    // The sum of all up to a-1 is F(a+1) - 1.
    // So here, the sum should be F(b+2) - F(a+1).
    static struct Digits ds{};
    // Need to make sure the answer is positive, as C++ mod allows negative.
    return (ds.digits[(to + 2) % 60] - ds.digits[(from + 1) % 60] + 10) % 10;
}

#if (not(defined(testing)) or testing == 0)
int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
#endif