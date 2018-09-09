#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <stdexcept>

using std::vector;
using std::string;

string largest_number(vector<string> as) {
    std::sort(std::begin(as), std::end(as), [&as](auto a, auto b) {
        return a + b > b + a;
    });

    std::stringstream ret;
    for (const auto &elem : as)
        ret << elem;
    return ret.str();
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);
}
