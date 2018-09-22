/**
 * job_queue.cpp
 *
 * By Sebastian Raaphost, 2018.
 *
 * Simulates process scheduling between multiple processors, with the goal to assign a process ASAP to the
 * free processor of lowest ID. We accomplish this using a min priority queue with key (time_available, worker-id),
 * and then iterate over the jobs, grabbing the min thread in the queue.
 *
 * We then re-enqueue the thread with its new time available.
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

using worker_id = size_t;
using process_time = unsigned long long;
using start_time   = unsigned long long;
using assignment = std::vector<std::pair<worker_id, start_time>>;

class JobQueue {
private:
    const size_t num_workers;

    // Priority queue setup. IDs are worker thread available time and then ID.
    // We want a min priority queue, so we must sort opposite to what we think.
    using thread_info = std::pair<start_time, worker_id >;
    struct Comparator {
        bool operator()(const thread_info &i1, const thread_info &i2) const {
            return !(i1.first < i2.first || (i1.first == i2.first && i1.second < i2.second));
        }
    };

public:
    assignment assign(std::vector<process_time> jobs) {
        // Entry at i represents the ith job, which is the thread ID and the start time.
        std::vector<std::pair<size_t, unsigned long long>> assignments;

        // Priority queue of worker threads, with priority being their available time and id.
        std::priority_queue<thread_info, std::deque<thread_info>, Comparator> thread_queue;
        for (auto idx = 0; idx < num_workers; ++idx)
            thread_queue.emplace(std::make_pair(0, idx));

        // Process all jobs.
        for (const auto ptime: jobs) {
            // Grab the first available thread.
            // I really wish Coursera would upgrade to C++117 so I could bind tuples.
            const auto thread_info = thread_queue.top();
            const auto stime       = thread_info.first;
            const auto id          = thread_info.second;
            thread_queue.pop();

            // Indicate when the thread will start the job.
            assignments.emplace_back(std::make_pair(id, stime));

            // Re-queue the worker thread.
            thread_queue.emplace(std::make_pair(stime + ptime, id));
        }
        return assignments;
    }

    JobQueue() = delete;
    explicit JobQueue(size_t num_workers) : num_workers{num_workers} {}
};

int main() {
    // Input.
    size_t num_workers, num_jobs;
    std::cin >> num_workers >> num_jobs;
    std::vector<process_time> processing_times;
    processing_times.resize(num_jobs);
    for (auto &processing_time: processing_times)
        std::cin >> processing_time;

    // Determine assignments.
    for (auto a: JobQueue{num_workers}.assign(processing_times))
        std::cout << a.first << ' ' << a.second << '\n';
}
