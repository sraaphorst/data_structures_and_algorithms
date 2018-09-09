# Uses python3
import sys
from collections import namedtuple

Segment = namedtuple('Segment', 'start end')


def intersect(s1, s2):
    start = max(s1.start, s2.start)
    end = min(s1.end, s2.end)
    if start > end:
        return None
    else:
        return Segment(start, end)


def optimal_points(segments):
    points = []

    # Sort the segments by start.
    segments = sorted(segments, reverse=True)
    while segments:
        segment = segments.pop()

        while segments and (intersect(segment, segments[-1])):
            segment = intersect(segment, segments.pop())
        points.append(segment.end)

    return points


if __name__ == '__main__':
    input = sys.stdin.read()
    n, *data = map(int, input.split())
    segments = list(map(lambda x: Segment(x[0], x[1]), zip(data[::2], data[1::2])))
    points = optimal_points(segments)
    print(len(points))
    for p in points:
        print(p, end=' ')
