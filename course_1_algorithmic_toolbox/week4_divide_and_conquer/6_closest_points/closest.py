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
    def aux(points):
        # Base case: 0 or 1 points.
        # It makes no sense to calculate a distance here, so return largest possible.
        if len(points) <= 1:
            return sys.maxsize

        # Base case: 2 points.
        if len(points) == 2:
            p, q = points
            print("p=({},{}), q=({},{}), dist={}".format(p[0], p[1], q[0], q[1], distance(p, q)))
            return distance(points[0], points[1])

        # Corner case: all points have the same x coordinate.
        # Since the points are sorted, we only need to check the first and last.
        # Then the distance is the minimum distance between the already sorted ys.
        if points[0][0] == points[-1][0]:
            # Find the y values closest together.
            distances = map(lambda p: p[1][1] - p[0][1], zip(points, points[1::]))
            #dist, p, q = min([(lambda p: p[1][1] - p[0][1],p,q) for p,q in zip(points, points[1::])])
            #print("p=({},{}), q=({},{}), dist={}".format(p[0], p[1], q[0], q[1], dist))
            #return min(distances)
            return min(distances)

        # Regular case: we have points on both sides. Try to draw a line through n/2 of them.
        # Note that if a lot of them are on this line, then the sizes will be very unequal.
        # We shove all points on the line to the left if the size of the left is smaller than the size of the right.
        #line = sum(map(lambda p: p[0], points))/2
        line = points[len(points)//2][0]
        left_points = list(takewhile(lambda p: p[0] < line, points))
        line_points = list(takewhile(lambda p: p[0] == line, points[len(left_points)::]))
        if len(left_points) < len(points) - len(left_points) - len(line_points):
            left_points.extend(line_points)
        right_points = points[len(left_points)::]
        d1 = min(aux(left_points), aux(right_points))

        # Now calculate the distance between the points in left_points and right_points.
        # Filter distance from the line and make sure points have distance at most d.
        left_in_bounds = list(dropwhile(lambda p: line - p[0] >= d1, left_points))
        right_in_bounds = list(takewhile(lambda p: p[0] - line <= d1, right_points))

        # Calculate the distances, provided there are any.
        if len(left_in_bounds) > 0 and len(right_in_bounds) > 0:
            le = enumerate(sorted(left_in_bounds, key=lambda p: p[1]))
            re = enumerate(sorted(right_in_bounds, key=lambda q: q[1]))
            #d3, p3, q3 = min([(distance(p, q), p, q) for i,p in le for j,q in re])
            d3, p3, q3 = min([(distance(p, q), p, q) for i,p in enumerate(left_in_bounds) for j,q in enumerate(right_in_bounds) if math.fabs((i - j) <= 7)])
            #d3,p3,q3 = min([(distance(p, q),p,q) for i,p in le for j,q in re])# if math.fabs(i - j) <= 7])
            print("***1: p=({},{}), q=({},{}), dist={}".format(p3[0], p3[1], q3[0], q3[1], d3))
            d2, p2, q2 = min([(distance(p, q), p, q) for p in left_in_bounds for q in right_in_bounds])
            print("***2: p=({},{}), q=({},{}), dist={}".format(p2[0], p2[1], q2[0], q2[1], d2))
            assert(d3 == d2 and p3 == p2 and q3 == q2)
            return min(d1, d2)
            return min(d1, d2)
        else:
            return d1

    points = list(zip(x, y))
    # We also want the ys sorted, but as an index into the xs.
    points.sort()
    return aux(points)

def brute_force(xs, ys):
    points = list(zip(xs, ys))
    dist, p, q = min([(distance(p, q), p, q) for i,p in enumerate(points) for j,q in enumerate(points) if i != j])
    print("Brute force: p=({},{}), q=({},{}), dist={}".format(p[0], p[1], q[0], q[1], dist))
    return dist

class TestClosest(unittest.TestCase):
    def test1(self):
        xs = [4, -2, -3, -1,  2, -4, 1, -1,  3, -4, -2]
        ys = [4, -2, -4,  3,  3,  0, 1, -1, -1,  2,  4]
        self.assertEqual(minimum_distance(xs, ys), math.sqrt(2))
    def test_random(self):
        num_points = randrange(2, 10**1)
        xs = [randrange(-10**1, 10**1) for _ in range(num_points)]
        ys = [randrange(-10**1, 10**1) for _ in range(num_points)]
        self.assertEqual(minimum_distance(xs, ys), brute_force(xs, ys))


if __name__ == '__main__':
    unittest.main()
    # input = sys.stdin.read()
    # data = list(map(int, input.split()))
    # n = data[0]
    # x = data[1::2]
    # y = data[2::2]
    # print("{0:.9f}".format(minimum_distance(x, y)))
