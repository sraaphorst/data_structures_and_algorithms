/**
 * lcs3.cpp
 *
 * By Sebastian Raaphorst, 2018.
 *
 * Given three sequences, find the length of the longest (not necessarily contiguous) subsequence they share in common
 * using dynamic programming.
 */

#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

using namespace std;

auto lcs3(const std::vector<int> &a, const std::vector<int> &b, const std::vector<int> &c) {
    auto m = a.size();
    auto n = b.size();
    auto p = c.size();

    size_t table[m + 1][n + 1][p + 1];

    // Now we iterate, beginning in the (0, 0, 0) corner.
    for (auto i = 0; i <= m; ++i)
        for (auto j = 0; j <= n; ++j)
            for (auto k = 0; k <= p; ++k) {
                // If any of the sequences are empty, there is nothing to match.
                // We don't explicitly have to do this since we already initialized all to 0, but for demonstration
                // purposes, we'll do it anyway.
                if (!(i && j && k))
                    table[i][j][k] = 0;

                // If the three are the same on the last digit, we have 1 + the smaller sequences.
                else if (a[i-1] == b[j-1] && b[j-1] == c[k-1])
                    table[i][j][k] = 1 + table[i-1][j-1][k-1];

                // If the characters of the sequences don't match, pick the largest out of the problem on the
                // subsequences.
                else
                    table[i][j][k] = std::max(table[i - 1][j][k], std::max(table[i][j - 1][k], table[i][j][k - 1]));
            }

    return table[m][n][p];
}

int main() {
    size_t an;

    std::cin >> an;
    std::vector<int> a(an);
    for (auto &elem: a)
        std::cin >> elem;

    size_t bn;
    std::cin >> bn;
    std::vector<int> b(bn);
    for (auto &elem: b)
        std::cin >> elem;

    size_t cn;
    std::cin >> cn;
    std::vector<int> c(cn);
    for (auto &elem: c)
        std::cin >> elem;

    std::cout << lcs3(a, b, c) << '\n';
}
