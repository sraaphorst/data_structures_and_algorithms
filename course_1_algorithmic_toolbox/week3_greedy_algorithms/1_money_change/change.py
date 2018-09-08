# Uses python3
import sys
import unittest

def get_change(m):
    return m // 10 + (m % 10) // 5 + m % 5
    return m

class TestChange(unittest.TestCase):
    def test_2(self):
        self.assertEqual(get_change(2), 2)
    def test_28(self):
        self.assertEqual(get_change(28), 6)

if __name__ == '__main__':
    #unittest.main()
    m = int(sys.stdin.read())
    print(get_change(m))
