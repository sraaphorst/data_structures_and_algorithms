#Uses python3
import math
import sys
import unittest
from itertools import takewhile, dropwhile
from random import randrange


# Trying to optimize here since the grader is fussy. Multiplication is much faster than exponentiation.
def distance(p, q):
    xdiff, ydiff = p[0] - q[0], p[1] - q[1]
    return math.sqrt(xdiff * xdiff + ydiff * ydiff)


def minimum_distance(x, y):
    # Duplicate points indicate that the answer is immediately 0.
    test = zip(x, y)
    if len(set(test)) < len(list(test)):
        return 0

    # Sort the xs, and the ys, and then make a map from x to y such that xtoymap(x[0]) gives the index of the
    # corresponding point in y.
    xs = list(map(lambda u: (u[0], u[1][0]), sorted(enumerate(zip(x, y)), key=lambda u: (u[1][0], u[1][1]))))
    ys = sorted(enumerate(y), key=lambda u: (u[1], u[0]))
    xtoymap = [j for x in xs for j in range(len(ys)) if x[0] == ys[j][0]]

    # We keep track of what xs we are looking at: [rangelower, rangeupper).
    def aux(rangelower, rangeupper):
        def indexed_distance(i, j):
            return distance((xs[rangelower+i][1], ys[xtoymap[rangelower+i]][1]),
                            (xs[rangelower+j][1], ys[xtoymap[rangelower+j]][1]))

        # This will come up frequently, so calculate it here once.
        size = rangeupper - rangelower

        # Base case: 0 or 1 points.
        # It makes no sense to calculate a distance here, so return largest possible.
        if size <= 1:
            return sys.maxsize

        # Base case: 2 points.
        if size == 2:
            return indexed_distance(0,1)

        # Corner case: all points have the same x coordinate.
        # Since the points are sorted, we only need to check the first and last.
        # Then the distance is the minimum distance between the already sorted ys.
        if xs[rangelower+0][1] == xs[rangeupper-1][1]:
            # Find the y values closest together.
            return min([ys[xtoymap[i]][1] - ys[xtoymap[i+1]][1] for i in range(rangelower, rangeupper)])

        # Regular case: we have points on both sides. Draw a line through n/2 of them.
        # It doesn't matter if some on the line end up in the left half or the right half.
        line = size//2 + rangelower + size % 2
        d1 = min(aux(rangelower, line), aux(line, rangeupper))

        # Now calculate the range of the points within distance d of the line between the two sets.
        # This will consist of the interval [rangelower + d_lower, rangelower + d_upper).
        d_lower = len(list(dropwhile(lambda u: xs[line][1] - xs[u][1] > d1, range(rangelower, line))))
        d_upper = len(list(takewhile(lambda u: xs[u][1] - xs[line][1] <= d1, range(line, rangeupper)))) + 1

        # Determine the calculations that need to be done for proximity to the line between the left side and
        # the right side.
        calcs = [(i, j)
                 for i in range(line - d_lower - rangelower, line - rangelower)
                 for j in range(line - rangelower, min(i + 8, line + d_upper - rangelower - 1))]

        # Calculate the distances, provided there are any.
        if len(calcs) > 0:
            d2 = min(indexed_distance(i, j) for i, j in calcs)
            return min(d1, d2)
        else:
            return d1

    return aux(0, len(xs))


def brute_force(xs, ys):
    points = list(zip(xs, ys))
    dist, p, q = min([(distance(p, q), p, q) for i,p in enumerate(points) for j,q in enumerate(points) if i != j])
    return dist


class TestClosest(unittest.TestCase):
    def test1(self):
        xs = [4, -2, -3, -1,  2, -4, 1, -1,  3, -4, -2]
        ys = [4, -2, -4,  3,  3,  0, 1, -1, -1,  2,  4]
        self.assertEqual(minimum_distance(xs, ys), math.sqrt(2))
    def test_random(self):
        num_points = randrange(2, 10**3)
        xs = [randrange(-10**9, 10**9) for _ in range(num_points)]
        ys = [randrange(-10**9, 10**9) for _ in range(num_points)]
        self.assertEqual(minimum_distance(xs, ys), brute_force(xs, ys))


if __name__ == '__main__':
    # unittest.main()
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    x = data[1::2]
    y = data[2::2]
    print("{0:.9f}".format(minimum_distance(x, y)))
