#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

using std::vector;
using std::string;

string largest_number(vector<string> a) {
    std::sort(std::begin(a), std::end(a), [](auto a, auto b) { return a.front() > b.front(); });

    std::stringstream ret;
    for (size_t i = 0; i < a.size(); i++) {
        ret << a[i];
    }
    string result;
    ret >> result;
    return result;
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
