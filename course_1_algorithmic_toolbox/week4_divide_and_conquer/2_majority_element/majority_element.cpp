#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// The recursive way. Represents the range [left, right).
// Note that we couldn't use auto here, as the compiler was choosing an unsigned type, thus making a count of -1
// equal to the maximum value.
int get_majority_element(const vector<int> &a, size_t left, size_t right) {
    const size_t size = right - left;

    // Base case: empty list.
    if (size == 0)
        return -1;

    // Base case: list of size 1, in which case, the only element is the majority element.
    if (size == 1)
        return a[left];

    // Divide in two.
    size_t k = (right + left) / 2;
    int e1 = get_majority_element(a, left, k);
    int e2 = get_majority_element(a, k, right);

    // If they agree, there is nothing to do.
    if (e1 == e2)
        return e1;

    // Otherwise, we have to count these two and see who wins, if either.
    long e1count = e1 >= 0 ? std::count(a.cbegin() + left, a.cbegin() + right, e1) : -1;
    long e2count = e2 >= 0 ? std::count(a.cbegin() + left, a.cbegin() + right, e2) : -1;

    long required = k - left;
    if (e1count > required)
        return e1;
    if (e2count > required)
        return e2;
    return -1;
}

// A cheating way, iterating over the array.
int get_majority_element_cheat(const vector<int> &a, size_t left, size_t right) {
    if (left == right) return -1;
    if (left + 1 == right) return a[left];

    std::map<int, size_t> counts;
    for (const auto elem: a)
        counts[elem] = 0;
    for (const auto elem: a)
        counts[elem] = counts[elem] + 1;

    for (const auto kv: counts)
        if (kv.second > a.size()/2)
            return 1;
    return -1;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (auto &elem : a) {
        std::cin >> elem;
    }
    cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
