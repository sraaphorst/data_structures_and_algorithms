/**
 * process_package.cpp
 *
 * By Sebastian Raaphorst, 2018.
 *
 * A network packet processor simulator. Packets arrive at a specified time, and if they cannot be buffered, they
 * are dropped; otherwise, they are processed after they arrive and when the processor is available.
 */

#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time{arrival_time},
        process_time{process_time}
    {}

    const int arrival_time;
    const int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped{dropped},
        start_time{start_time}
    {}

    const bool dropped;
    const int start_time;

};

std::ostream &operator<<(std::ostream &out, const Response &r) {
    return out << (r.dropped ? -1 : r.start_time);
}


class Buffer {
public:
    explicit Buffer(int size):
        size{size},
        finish_time{}
    {}

    Response Process(const Request &request) {
        // Determine when the processor will be available: if the queue is empty, it is
        // available now; otherwise, when the last task in the queue has completed.
        const auto available = finish_time.empty() ? 0 : finish_time.back();

        // Process all tasks on the queue that can be done prior to the arrival of the request and pop them.
        while (!finish_time.empty() && finish_time.front() <= request.arrival_time)
            finish_time.pop_front();

        // If the queue is full, drop it.
        if (finish_time.size() >= size)
            return Response{true, 0};

        // Otherwise, enqueue and return the starting time.
        // This is the maximum of when the processor is available and when the task arrived.
        const auto start_time = std::max(available, request.arrival_time);
        finish_time.emplace_back(start_time + request.process_time);
        return Response{false, start_time};
    }

private:
    const int size;
    std::deque<int> finish_time;
};


std::vector<Request> ReadRequests() {
    std::vector<Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.emplace_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector<Response> ProcessRequests(const std::vector<Request> &requests, Buffer &buffer) {
    std::vector<Response> responses;
    for (const auto &request: requests)
        responses.emplace_back(buffer.Process(request));
    return responses;
}

void PrintResponses(const std::vector<Response> &responses) {
    std::copy(responses.cbegin(), responses.cend(), std::ostream_iterator<const Response&>(std::cout, "\n"));
}

int main() {
    int size;
    std::cin >> size;
    std::vector<Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector<Response> responses = ProcessRequests(requests, buffer);

    PrintResponses(responses);
    return 0;
}
