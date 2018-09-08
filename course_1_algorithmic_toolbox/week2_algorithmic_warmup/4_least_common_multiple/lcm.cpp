#include <iostream>

#ifdef testing
#include "lcm.h"
#endif

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

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

long long lcm_fast(int a, int b) {
    return ((long long)a) * ((long long)b) / gcd_euclidean(a,b);
}

#ifndef testing
int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
#endif
