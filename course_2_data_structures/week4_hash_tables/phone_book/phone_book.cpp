/**
 * phone_book.cpp
 *
 * By Sebastian Raaphorst, 2018.
 *
 * Direct addressing implementation of a phone book.
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

using phone_name = std::string;
using phone_number = size_t;

enum class Request {
    add,
    del,
    find,
};

struct Query {
    Request type;
    phone_name name;
    phone_number number;
};


class PhoneBook {
    constexpr static const size_t num_entries = 10'000'000;
    std::string *entries;

public:
    PhoneBook() {
        entries = new std::string[num_entries];
        std::for_each(entries, entries + num_entries, [](auto &entry) { entry = ""; });
    }

    PhoneBook(const PhoneBook &) = delete;

    PhoneBook(PhoneBook &&) = delete;

    PhoneBook &operator=(const PhoneBook &) = delete;

    ~PhoneBook() {
        delete[] entries;
    }

    std::string &operator[](size_t idx) {
        return entries[idx];
    }

    const std::string &operator[](size_t idx) const {
        return entries[idx];
    }
};


std::vector<Query> read_queries() {
    // Number of operations.
    size_t n;
    std::cin >> n;

    std::vector<Query> queries(n);
    for (auto &query: queries) {
        std::string type_name;
        std::cin >> type_name;
        if (type_name == "add") {
            query.type = Request::add;
            std::cin >> query.number >> query.name;
        } else if (type_name == "del") {
            query.type = Request::del;
            std::cin >> query.number;
        } else {
            query.type = Request::find;
            std::cin >> query.number;
        }
    }
    return queries;
}

std::vector<std::string> process_queries(const std::vector<Query> &queries) {
    PhoneBook book;
    std::vector<std::string> result;

    // Keep list of all existing (i.e. not deleted yet) contacts.
    std::vector<Query> contacts;
    for (const auto &query: queries) {
        switch (query.type) {
            case Request::add:
                book[query.number] = query.name;
                break;
            case Request::del:
                book[query.number] = "";
                break;
            case Request::find:
                result.emplace_back(book[query.number].empty() ? "not found" : book[query.number]);
                break;
        };
    }
    return result;
}

void write_responses(const std::vector<std::string> &result) {
    std::copy(std::cbegin(result), std::cend(result), std::ostream_iterator<std::string>(std::cout, "\n"));
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
