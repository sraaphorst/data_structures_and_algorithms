#include <iostream>
#include <vector>

#ifdef testing
#include "fibonacci_sum_last_digit.h"
#endif

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
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

int fibonacci_sum_fast(long long n) {
    // The sum of the first N fib digits is F(n+2) - 1.
    // This could be negative if the last digit of F(n+2) is 0.
    // Thus, we add 10 and take mod 10 to give us:
    // (F(n+2) + 9) % 10.
    static struct Digits ds{};
    return (ds.digits[(n + 2) % 60] + 9) % 10;
}

#ifndef testing
int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n);
}
#endif