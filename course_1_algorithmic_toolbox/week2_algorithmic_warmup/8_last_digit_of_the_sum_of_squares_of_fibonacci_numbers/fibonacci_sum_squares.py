# Uses python3
from sys import stdin
import unittest

def fibonacci_sum_squares_naive(n):
    if n <= 1:
        return n

    previous = 0
    current  = 1
    sum      = 1

    for _ in range(n - 1):
        previous, current = current, previous + current
        sum += current * current

    return sum % 10

# Formulate the Pisano sequence, i.e. the fibonacci numbers mod 10, which has period 60.
fib_digits = [0,1]
for i in range(2,60):
    fib_digits.append((fib_digits[i-1] + fib_digits[i-2]) % 10)

def fibonacci_sum_squares_fast(n):
    return (fib_digits[n % 60] * (fib_digits[n % 60] + fib_digits[(n-1) % 60])) % 10

class TestFib(unittest.TestCase):
    def test_7(self):
        self.assertEqual(fibonacci_sum_squares_fast(7), 3)
    def test_73(self):
        self.assertEqual(fibonacci_sum_squares_fast(73), 1)
    def test_1234567890(self):
        self.assertEqual(fibonacci_sum_squares_fast(1234567890), 0)


if __name__ == '__main__':
    #unittest.main()
    n = int(stdin.read())
    print(fibonacci_sum_squares_fast(n))
