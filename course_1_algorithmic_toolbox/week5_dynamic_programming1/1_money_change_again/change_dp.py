# Uses python3

# change_dp.py
#
# By Sebastian Raaphorst, 2018.
#
# Given a value and a list of denominations of coins, find the minimal number of coins needed to make that value.
# I implement a recursive and dynamic programming strategy.

import sys


def get_change(m):
    # Technique 1: recursion.
    # The problem with recursion is that we are limited to m being the permitted stack depth.
    # For example, using recursion, we cannot calculate the answer for 1234567.
    def rec(m, denominations):
        # Base case: done.
        if m == 0:
            return 0

        # Cut out all denominations that cannot be used.
        while m < denominations[0]:
            denominations = denominations[1:]

        # Short circuit: If all we have left are denomination 1 coins, then we need m of them.
        if len(denominations) == 1:
            return m

        # Recurse into two cases:
        # 1. Using a coin of size denominations[0].
        # 2. Not using any more coins of denominataions[0].
        return min(1 + rec(m - denominations[0], denominations), rec(m, denominations[1:]))

    # Technique 2: dynamic programming.
    # This works for any m. For 1234567, the answer is 308642.
    def dp(m, denominations):
        # Create an array of size m+1, to represent the partial answers for all m' <= m..
        array_m = [0] * (m+1)

        i = 0
        while (i <= m):
            candidates = list(map(lambda x: array_m[x], filter(lambda x: x >= 0, [i - d for d in denominations])))
            if len(candidates) > 0:
                array_m[i] = min(candidates) + 1
            else:
                array_m[i] = 0
            i += 1

        return array_m[m]

    # return rec(m, [4, 3, 1])
    return dp(m, [4, 3, 1])


if __name__ == '__main__':
    m = int(sys.stdin.read())
    print(get_change(m))
