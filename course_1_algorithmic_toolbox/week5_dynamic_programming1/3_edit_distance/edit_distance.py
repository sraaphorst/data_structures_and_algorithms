# Uses python3

# edit_distance.py
#
# By Sebastian Raaphorst, 2018.
#
# Given two strings, find the minimum number of operations needed to change one to the other, with allowed operations
# being to delete a character, to insert a character, and to change a character, using dynamic programming.

def edit_distance(s, t):
    # Operations: insert, delete, change.
    # Create a table to hold the intermediate calculations.
    m, n = len(s), len(t)
    table = [([0] * (n + 1))[:] for i in range(m + 1)]

    # Now fill the table bottom-up, with entry[i][j] being the number of operations to go from a string of
    # length i to a string of length j.
    for i in range(m + 1):
        for j in range(n + 1):
            # If the first string is empty, our only option is to insert all characters of the second string.
            if i == 0:
                table[i][j] = j

            # If the second string is empty, our only option is to remove all characters in the first string.
            elif j == 0:
                table[i][j] = i

            # Check the last characters to see if they are the same.
            # If so, ignore and recurse.
            elif s[i-1] == t[j-1]:
                table[i][j] = table[i-1][j-1]

            # If the last characters are different, find the minimum of all the possibilities.
            else:
                # table[i][j - 1] = insert
                # table[i - 1][j] = delete
                # table[i - 1][j - 1] = change
                table[i][j] = 1 + min(table[i][j - 1], table[i - 1][j], table[i - 1][j - 1])

    return table[m][n]


if __name__ == "__main__":
    print(edit_distance(input(), input()))
