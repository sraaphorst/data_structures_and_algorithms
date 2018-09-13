# Uses python3
import sys


def merge(b, c):
    result = []
    inversions = 0
    while b and c:
        if b[0] <= c[0]:
            result.append(b.pop(0))
        else:
            result.append(c.pop(0))
            inversions += len(b)
    result += b or c
    return result, inversions


def inversions(a):
    if len(a) == 1:
        return a, 0

    mid = len(a) // 2
    lft, lft_inv = inversions(a[:mid])
    rgt, rgt_inv = inversions(a[mid:])

    merged, merged_inv = merge(lft, rgt)
    return merged, merged_inv + lft_inv + rgt_inv


if __name__ == '__main__':
    input = sys.stdin.read()
    n, *a = list(map(int, input.split()))
    b = n * [0]
    print(inversions(a)[1])
