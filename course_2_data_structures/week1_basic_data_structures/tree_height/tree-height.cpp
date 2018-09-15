/**
 * tree-height.cpp
 *
 * By Sebastian Raaphorst, 2018.
 *
 * Non-recursive, queue-based algorithm to determine the height of an arbitrary tree.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

class Node final {
public:
    size_t key;
    Node *parent;
    std::vector<Node*> children;

    Node(): key{0}, parent{nullptr} {}

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.emplace_back(this);
    }

    // Get the height of the tree at this node in a non-recursive fashion.
    size_t getHeight() const {
        using info = std::pair<const Node*, size_t>;
        size_t height = 0;

        std::queue<info> nodes;
        nodes.emplace(std::make_pair(this, 1));
        while (!nodes.empty()) {
            const auto finfo = nodes.front();
            nodes.pop();

            if (finfo.second > height)
                height = finfo.second;

            for (const auto n: finfo.first->children)
                nodes.emplace(std::make_pair(n, finfo.second + 1));
        }

        return height;
    }
};

int main() {
    size_t n;
    std::cin >> n;

    // Read in the tree.
    std::vector<Node> nodes;
    nodes.resize(n);

    for (size_t child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        nodes[child_index].key = child_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
    }

    // Get the root.
    const auto iter = std::find_if(nodes.cbegin(), nodes.cend(), [](const auto &n) { return n.parent == nullptr; });
    std::cout << ((iter != nodes.cend()) ? iter->getHeight() : 0) << '\n';
}
