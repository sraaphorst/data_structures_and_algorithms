/**
 * build_heap.cpp
 *
 * By Sebastian Raaphorst, 2018.
 *
 * Given an array, make it into a valid min-heap, recording the given swaps.
 * This entails sifting down on each element in reverse order, excluding the last row (where there is nothing
 * to sift down). After siftDown(i) has completed, the tree rooted at i is a min-heap.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

class HeapBuilder {
private:
    std::vector<int> data;
    std::vector<std::pair<size_t, size_t>> swaps;

    void writeResponse() const {
        std::cout << swaps.size() << "\n";
        for (const auto swap: swaps)
            std::cout << swap.first << " " << swap.second << '\n';
    }

    void readData() {
        int n;
        std::cin >> n;
        data.resize(n);
        for (auto &d: data)
            std::cin >> d;
    }


    void siftDown(size_t idx) {
        std::array<size_t, 3> candidates = {{idx, 2 * idx + 1, 2 * idx + 2}};
        size_t left    = 2 * idx + 1;
        size_t right   = 2 * idx + 2;

        size_t smallidx = idx;
        if (left < data.size() && data[left] < data[smallidx])
            smallidx = left;
        if (right < data.size() && data[right] < data[smallidx])
            smallidx = right;

        if (smallidx != idx) {
            swaps.emplace_back(std::make_pair(idx, smallidx));
            std::swap(data[idx], data[smallidx]);
            siftDown(smallidx);
        }
    }

    void generateSwaps() {
        swaps.clear();
        for (int idx = data.size() / 2; idx >= 0; --idx)
            siftDown(idx);
    }

public:
    void solve() {
        readData();
        generateSwaps();
        writeResponse();
    }
};

int main() {
    HeapBuilder{}.solve();
}
