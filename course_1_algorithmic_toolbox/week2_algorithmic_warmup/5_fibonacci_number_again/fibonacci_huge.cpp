#include <algorithm>
#include <iostream>
#include <vector>

#ifdef testing
#include "fibonacci_huge.h"
#endif

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

// Find the period of the fib numbers mod m.
// Continue to calculate until the latter half of the array is identical to the former half.
// Then chop the latter half off and return the first half. (Not really necessary to do, but for neatness.)
// We could have also just scanned for 0 1 appearing and then cut them off and returned the rest.
std::vector<long long> period_mod_m(long long m) {
    std::vector<long long> remainders;
    for (long long i = 0;i < m*m+1;++i) {
        remainders.emplace_back(get_fibonacci_huge_naive(i, m));
        if (remainders.size() % 2 == 0 && std::equal(remainders.cbegin(), remainders.cbegin() + remainders.size()/2, remainders.cbegin() + remainders.size()/2)) {
            remainders.erase(remainders.cbegin() + remainders.size()/2, remainders.cend());
            return remainders;
        }
    }
}

long long period_length(long long m) {
    long long prev = 0, cur = 1;
    for (auto i = 2; i <= m*m; ++i) {
        prev = (prev + cur) % m;
        std::swap(prev, cur);
        if (prev == 0 && cur == 1)
            return i - 1;
    }
}

auto fibonacci_fast(long long n, long long m) {
    if (n <= 1) return n;
    long long prev = 0;
    long long cur = 1;
    for (int i = 2; i <= n; ++i) {
        prev = (prev + cur) % m;
        std::swap(cur, prev);
    }
    return cur;
}

long long get_fibonacci_huge_fast(long long n, long long m) {
    auto per = period_length(m);
    return fibonacci_fast(n % period_length(m), m);
}

#ifndef testing
int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
#endif