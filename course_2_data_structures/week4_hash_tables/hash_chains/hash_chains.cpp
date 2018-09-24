/**
 * hash_chains.cpp
 *
 * By Sebastian Raaphorst, 2018.
 *
 * Basic set implementation using hashing with a specified number of buckets.
 */

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

class QueryProcessor final {
    using data = std::string;
    using hashchain = std::vector<data>;
    using hashtable = std::vector<hashchain>;

    const size_t bucket_count;

    // The hashtable, consisting of bucket_count vectors of string.
    hashtable table;

    // Calculate the hash of the data.
    size_t hash_func(const data &s) const {
        constexpr static const size_t multiplier = 263;
        constexpr static const size_t prime = 1'000'000'007;

        // Iterate over the string in reverse.
        unsigned long long hash = 0;
        for (auto iter = std::rbegin(s); iter != std::rend(s); ++iter)
            hash = (hash * multiplier + *iter) % prime;

        // We want a positive value.
        return ((hash % bucket_count) + bucket_count) % bucket_count;
    }

public:
    explicit QueryProcessor(size_t bucket_count):
        bucket_count(bucket_count),
        table{hashtable(bucket_count)} {}


    // Process a query, depending on type.
    void readAndExecuteQuery(std::istream &in, std::ostream &out) {
        // Fetch the query type.
        std::string query_type;
        in >> query_type;

        /*** CHECK QUERY ***/
        if (query_type == "check") {
            // Read the row of the table to output.
            size_t index;
            in >> index;

            std::copy(std::crbegin(table[index]), std::crend(table[index]), std::ostream_iterator<data>(out, " "));
            out << '\n';
            return;
        }

        // Any of the other queries rely on a key, so get:
        // 1. The chain that would contain this key (i.e. the chain index to which it would hash); and
        // 2. An iterator to the key, if one exists.
        data key;
        in >> key;
        auto &chain = table[hash_func(key)];
        const auto iter = std::find(std::cbegin(chain), std::cend(chain), key);

        /*** FIND ***/
        if (query_type == "find") {
            out << (iter == std::cend(chain) ? "no" : "yes") << '\n';
            return;
        }

        /*** ADD ***/
        if (query_type == "add") {
            if (iter == std::cend(chain))
                chain.emplace_back(key);
            return;
        }

        /*** DEL ***/
        if (query_type == "del") {
            if (iter != std::cend(chain))
                chain.erase(iter);
            return;
        }
    }
};

int main() {
    // Determine the number of buckets and create the query processor.
    size_t bucket_count;
    std::cin >> bucket_count;
    QueryProcessor proc(bucket_count);

    // Determine the number of queries and process them one-by-one.
    size_t n;
    std::cin >> n;
    for (auto i = 0; i < n; ++i)
        proc.readAndExecuteQuery(std::cin, std::cout);

    return 0;
}
