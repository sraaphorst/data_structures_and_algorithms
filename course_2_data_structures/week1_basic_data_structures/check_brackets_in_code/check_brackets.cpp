/**
 * check_brackets.cpp
 *
 * By Sebastian Raaphorst, 2018.
 *
 * A simple, stack-based bracket balancer.
 */

#include <iostream>
#include <memory>
#include <stack>
#include <string>

class Result {
protected:
    Result() = default;

public:
    virtual std::string to_string() const = 0;

    friend std::ostream &operator<<(std::ostream &out, const Result &result) {
        return out << result.to_string();
    }
};

namespace details {
    class Bracket {
    public:
        Bracket(const char type, const size_t position) :
                type{type},
                position{position} {}

        auto match(char c) const {
            return (type == '[' && c == ']')
                   || (type == '{' && c == '}')
                   || (type == '(' && c == ')');
        }

        auto getPosition() const {
            return position;
        }

    private:
        const char type;
        const size_t position;
    };

    class Success final: public Result {
    public:
        std::string to_string() const override {
            return "Success";
        }
    };

    class Failure final: public Result {
    public:
        explicit Failure(size_t position) :
                position{position} {}

        // The assignment wants 1-based positioning.
        std::string to_string() const override {
            return std::to_string(position + 1);
        };
    private:
        const size_t position;
    };
}

const std::unique_ptr<Result> checkBrackets(const std::string &text) {
    std::stack<details::Bracket> brackets;

    for (size_t position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{')
            brackets.emplace(details::Bracket(next, position));
        else if (next == ')' || next == ']' || next == '}') {
            // Fail cases:: stack is empty or bracket mismatch.
            if (brackets.empty() || !brackets.top().match(next))
                return std::make_unique<details::Failure>(position);

            // Otherwise, we have matched, so pop and continue.
            brackets.pop();
        }
    }

    return brackets.empty() ?
        std::unique_ptr<Result>{new details::Success()} :
        std::unique_ptr<Result>{new details::Failure{brackets.top().getPosition()}};
}

int main() {
    std::string text;
    getline(std::cin, text);
    std::cout << *checkBrackets(text);
    return 0;
}
