#include <algorithm>
#include <iostream>
#include <random>
#include <utility>

#ifdef testing
#include "gcd.h"
#endif

int gcd_naive(int a, int b) {
    int current_gcd = 1;
    for (int d = 2; d <= a && d <= b; d++) {
        if (a % d == 0 && b % d == 0) {
            if (d > current_gcd) {
                current_gcd = d;
            }
        }
    }
    return current_gcd;
}

/// My implementation.
int gcd_euclidean(int a, int b) {
  int prevr=b, r;

  for (;;) {
    r = a % b;
    if (!r)
      return prevr;
    prevr = r;
    a = b;
    b = r;
  }
}

#ifndef testing
int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd_euclidean(a, b) << std::endl;
  return 0;
}
#endif