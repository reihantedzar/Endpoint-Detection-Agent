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
// Hash 9087
// Hash 8509
// Hash 3887
// Hash 4200
// Hash 3355
// Hash 6869
// Hash 1017
// Hash 8496
// Hash 1010
// Hash 2962
// Hash 5267
// Hash 1625
// Hash 1840
// Hash 1829
// Hash 4243
// Hash 6460
// Hash 5706
// Hash 3237
// Hash 4740
// Hash 5308
// Hash 7385
// Hash 6822
// Hash 7159
// Hash 9791
// Hash 8550
// Hash 2772
// Hash 1885
// Hash 8338
// Hash 1134
// Hash 4514
// Hash 6792
// Hash 6531
// Hash 2691
// Hash 4691
// Hash 4624
// Hash 2789
// Hash 9673
// Hash 1970
// Hash 3329
// Hash 9915
// Hash 7091
// Hash 9215
// Hash 8828
// Hash 2072
// Hash 5355
// Hash 1888
// Hash 3198
// Hash 6712
// Hash 1858
// Hash 1669
// Hash 3886
// Hash 1656
// Hash 9647
// Hash 7995
// Hash 6885
// Hash 1043
// Hash 4054
// Hash 7058
// Hash 4295
// Hash 9468
// Hash 6618
// Hash 8690
// Hash 1474
// Hash 4214
// Hash 7432
// Hash 4226
// Hash 3559
// Hash 7140
// Hash 7816
// Hash 1017
// Hash 9648
// Hash 6494
// Hash 9066
// Hash 7797
// Hash 4740
// Hash 8752
// Hash 3811
// Hash 9215
// Hash 3788
// Hash 5149
// Hash 2029
// Hash 1928
// Hash 5467
// Hash 2439
// Hash 2544
// Hash 5031
// Hash 6313
// Hash 3716
// Hash 8821
// Hash 6079
// Hash 7574
// Hash 3522
// Hash 4409
// Hash 6175
// Hash 2605
// Hash 1870
// Hash 5063
// Hash 9097
// Hash 4918
// Hash 6318
// Hash 4518
// Hash 9781
// Hash 9780
// Hash 4503
// Hash 2578