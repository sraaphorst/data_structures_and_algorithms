#include <iostream>
#include <vector>

#ifdef testing
#include "fibonacci_last_digit.h"
#endif

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

// The fibonacci numbers repeat last digit every 60, so we only need to determine up to 60 and then take mod 60
// to get the last digit.
struct Digits {
    std::vector<int> digits{60};
    Digits() {
        digits[0] = 0;
        digits[1] = 1;
        for (int i = 2; i < 60; ++i)
            digits[i] = (digits[i - 1] + digits[i - 2]) % 10;
    }
};

int get_fibonacci_last_digit_fast(int n) {
    static struct Digits ds{};
    return ds.digits[n % 60];
}

#ifndef testing
int main() {
    int n;
    std::cin >> n;
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
}
#endif