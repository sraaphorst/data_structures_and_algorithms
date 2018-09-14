# Uses python3
import sys


def optimal_weight(capacity, weights):
    # Create an array to store the maximum possible weight that can be taken up to capacity.
    # caps = [0] * (capacity + 1)
    #
    # for c in range(1, capacity + 1):
    #     # We take the bar that, if possible, will bring us closest to this capacity.
    #     candidates = list(filter(lambda x: x <= c, enumerate(weights)))
    #     print("Candidates for cap {} are {}".format(c, list(candidates)))
    #     print([x + caps[c - x] for x in candidates])
    #     caps[c] = max(list(map(lambda x: x + caps[c - x], candidates)) + [0])
    #     print("\tselecting: {}".format(caps[c]))
    # print(caps)
    # return caps[capacity]
    bars = len(weights)

    # We want values such that table[i][w] indicates the maximum weight that can fit in w using the first
    # i bars.
    table = [([0] * (capacity + 1))[:] for i in range(bars + 1)]

    # Initialize: for zero items, all maximum weights are zero.
    for i in range(capacity + 1):
        table[0][i] = 0

    for i in range(1, bars + 1):
        for c in range(capacity + 1):
            # If we can't accommodate this item, then there's nothing to do.
            if w[i - 1] > c:
                table[i][c] = table[i - 1][c]
            else:
                table[i][c] = max(table[i - 1][c], table[i - 1][c - w[i - 1]] + w[i - 1])

    return table[bars][capacity]


if __name__ == '__main__':
    input = sys.stdin.read()
    W, n, *w = list(map(int, input.split()))
    print(optimal_weight(W, w))
