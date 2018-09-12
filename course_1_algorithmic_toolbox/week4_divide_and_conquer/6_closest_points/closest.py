#Uses python3
import sys
import math
from itertools import takewhile, dropwhile

def minimum_distance(x, y):
    # Trying to optimize here since the grader is fussy. Multiplication is much faster than exponentiation.
    def distance(p, q):
        xdiff, ydiff = p[0] - q[0], p[1] - q[1]
        return math.sqrt(xdiff * xdiff + ydiff * ydiff)

    def aux(points):
        # Base case: 0 or 1 points.
        # It makes no sense to calculate a distance here, so return largest possible.
        if len(points) <= 1:
            return sys.maxsize

        # Base case: 2 points.
        if len(points) == 2:
            return distance(points[0], points[1])

        # Corner case: all points have the same x coordinate.
        # Since the points are sorted, we only need to check the first and last.
        # Then the distance is the minimum distance between the already sorted ys.
        if points[0][0] == points[-1][0]:
            # Find the y values closest together.
            distances = map(lambda p: p[1][1] - p[0][1], zip(points, points[1::]))
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
            d2 = min([distance(p, q) for p in left_in_bounds for q in right_in_bounds])
            return min(d1, d2)
        else:
            return d1

    points = list(zip(x, y))
    points.sort()
    return aux(points)


if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    x = data[1::2]
    y = data[2::2]
    print("{0:.9f}".format(minimum_distance(x, y)))
