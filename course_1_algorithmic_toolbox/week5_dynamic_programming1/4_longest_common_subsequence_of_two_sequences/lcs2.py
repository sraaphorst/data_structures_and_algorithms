#Uses python3

# lcs.py
#
# By Sebastian Raaphorst, 2018.
#
# Given two sequences, find the length of the longest (not necessarily contiguous) subsequence they share, using
# dynamic programming.

import sys

def lcs2(a, b):
    m, n = len(a), len(b)

    # Create a table to represent the problem intermediate solutions.
    table = [([0] * (n + 1))[:] for i in range(m + 1)]

    # Work backwards, matching from the end.
    for i in range(m + 1):
        for j in range(n + 1):
            # If either sequence is empty, there is nothing to match.
            if i == 0 or j == 0:
                table[i][j] = 0

            # If they match, record this.
            elif a[i - 1] == b[j - 1]:
                table[i][j] = 1 + table[i - 1][j - 1]

            # Else, they do not match, so pick the maximum value of the two subsequences
            # that match.
            else:
                table[i][j] = max(table[i - 1][j], table [i][j - 1])

    return table[m][n]


if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))

    n = data[0]
    data = data[1:]
    a = data[:n]

    data = data[n:]
    m = data[0]
    data = data[1:]
    b = data[:m]

    print(lcs2(a, b))
