//
// Created by tomfr on 09/10/2024.
//

#ifndef TP_BARRIER_HPP
#define TP_BARRIER_HPP
#include <condition_variable>
#include <mutex>

class Barrier {
private:
    std::mutex mtx;
    std::condition_variable cv;
    unsigned int thread_amount;
    unsigned int thread_waiting;
public:
    Barrier();
    Barrier(unsigned int count);
    void wait();
};


#endif //TP_BARRIER_HPP
