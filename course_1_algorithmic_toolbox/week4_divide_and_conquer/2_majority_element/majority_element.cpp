#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using std::vector;

int get_majority_element_aux(vector<int> &a, int left, int right) {
    const auto size = right - left;
    if (size == 1)
        return a[left];
    if (size == 0)
        return -1;

    auto k = (right + left) / 2;
    auto e1 = get_majority_element_aux(a, left, k);
    auto e2 = get_majority_element_aux(a, k + 1, right);

    if (e1 == e2)
        return e1;

    auto e1count = e1 >= 0 ? std::count(a.cbegin() + left, a.cbegin() + right, e1) : -1;
    auto e2count = e2 >= 0 ? std::count(a.cbegin() + left, a.cbegin() + right, e2) : -1;

    if (e1count > k)
        return e1;
    if (e2count > k)
        return e2;
    return -1;
}
int get_majority_element(vector<int> &a, int left, int right) {
//    if (left == right) return -1;
//    if (left + 1 == right) return a[left];
//
//    std::map<int, size_t> counts;
//    for (const auto elem: a)
//        counts[elem] = 0;
//    for (const auto elem: a)
//        counts[elem] = counts[elem] + 1;
//
//    for (const auto kv: counts)
//        if (kv.second > a.size()/2)
//            return 1;
//    return -1;
    return (get_majority_element_aux(a, left, right) >= 0) ? 1 : -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
