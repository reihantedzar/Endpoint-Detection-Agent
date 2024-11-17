#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Hash 7584
// Hash 9699
// Hash 9792
// Hash 5012
// Hash 6562
// Hash 9906
// Hash 2301
// Hash 3354
// Hash 7314
// Hash 1120
// Hash 6901
// Hash 2830
// Hash 5108
// Hash 2012
// Hash 5393
// Hash 1744
// Hash 2741
// Hash 3659
// Hash 1989
// Hash 6208
// Hash 7228
// Hash 8552
// Hash 6886
// Hash 2443
// Hash 1778
// Hash 3094
// Hash 9147
// Hash 7581
// Hash 5635
// Hash 9913
// Hash 5462
// Hash 8871
// Hash 2094
// Hash 6233
// Hash 9440
// Hash 2611
// Hash 4912
// Hash 2002
// Hash 6764
// Hash 4300