#Uses python3

import sys
import unittest

def max_dot_product(a, b):
    a = list(reversed(sorted(a)))
    b = list(reversed(sorted(b)))

    res = 0
    for i in range(len(a)):
        res += a[i] * b[i]
    return res

class TestDotProduct(unittest.TestCase):
    def test1(self):
        self.assertEqual(max_dot_product([23], [39]), 897)

    def test2(self):
        self.assertEqual(max_dot_product([1, 3, -5], [-2, 4, 1]), 23)

if __name__ == '__main__':
    #unittest.main()
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    a = data[1:(n + 1)]
    b = data[(n + 1):]
    print(max_dot_product(a, b))
    
