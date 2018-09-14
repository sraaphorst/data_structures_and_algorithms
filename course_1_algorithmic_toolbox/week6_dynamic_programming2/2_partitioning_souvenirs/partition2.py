#!/usr/bin/env python3

# By Sebastian Raaphorst, 2018.
#
# Goal: partitioning a set of values into two subsets of equal value.
# This is in preparation for partition3.py, as solving this problem first will help me understand that problem
# better.

import unittest
import itertools
from random import randrange

def partition2(items):
    """
    partition2(items)

    This takes a list of items represented by their numeric value, and using dynamic programming, determines
    if we can find a partition of items into two sunsets such that they have the same value.

    Returns True or False.

    """

    # This can only be done IF the sum of the item values is even.
    totalval = sum(items)
    if totalval % 2 and max(items) <= totalval // 2:
        return False

    # Column j will represent the results over the first j items, with column 0 being the empty set.
    # Row i will represent if we can form a set of value i.
    # Thus table[i][j] indicates if we can find a subset amongst the first j items that sums to i.
    rows = totalval // 2 + 1
    cols = len(items) + 1

    table = [([False] * cols)[:] for _ in range(rows)]

    # Initialize the first row and column, even though we won't technically use the first row; it just simplifies
    # accessing.
    #
    # Column 0 is (apart from entry in row 0) all False since we cannot form any value other than zero from the
    # empty set. This was already set by the table initializer.
    #
    # Row 0 is all True, since we can form the value 0 simply by taking no items.
    for c in range(cols):
        table[0][c] = True

    # Start calculating at (1,1), moving left-to-right, and then top-to-bottom.
    for r in range(1, rows):
        for c in range(1, cols):
            # Cases:
            # 1. Item represented by column c (i.e. item c - 1) perfectly gives the value r.
            # 2. We already found a combination of items that gives value r in the previous row contents.
            # In both these cases, the answer is obviously True.
            if items[c - 1] == r or table[r][c - 1]:
                table[r][c] = True
            else:
                # Determine the remaining value needed if we took the current item under consideration.
                # We know from case (1) above that it is not equal to value r.
                remain = r - items[c - 1] # Not zero

                # If item c - 1 fits and the remaining value amongst the previous items equals the remaining value,
                # then obviously, we can form value r by taking this item and the ones to form value remain.
                if remain > 0 and table[remain][c - 1]:
                    table[r][c] = True

    return table[-1][-1]

# Brute force algorithm that guarantees the correct solution, but in exponential time.
# We do this by checking every partition, which amounts to checking for all subsets.
def partition2_brute(items):
    # Generate the power set of a set.
    def powerset(iterable):
        s = list(iterable)
        return itertools.chain.from_iterable(itertools.combinations(s, r) for r in range(len(s) + 1))

    totalval = sum(items)
    if totalval % 2:
        return False
    desiredval = totalval // 2

    subsetevaluations = (sum(x) for x in powerset(items))
    return desiredval in subsetevaluations



class TestPartitioning(unittest.TestCase):
    def test_brute1(self):
        items = [1, 3, 3, 2, 2, 1]
        self.assertTrue(partition2_brute(items))

    def test_brute2(self):
        items = [7, 2, 1, 3, 2, 1]
        self.assertTrue(partition2_brute(items))

    def test_random(self):
        numitems = randrange(20)
        items = [randrange(30) for _ in range(numitems)]
        self.assertEqual(partition2_brute(items), partition2(items))


if __name__ == "__main__":
    unittest.main()