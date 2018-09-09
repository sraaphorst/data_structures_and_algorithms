# Uses python3
import sys


def optimal_summands(n):
    if not n:
        return []

    summands = [1]
    n = n - 1

    while n > summands[-1]:
        summands.append(summands[-1] + 1)
        n = n - summands[-1]
    summands[-1] = summands[-1] + n
    return summands


if __name__ == '__main__':
    input = sys.stdin.read()
    n = int(input)
    summands = optimal_summands(n)
    print(len(summands))
    for x in summands:
        print(x, end=' ')
