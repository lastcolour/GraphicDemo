// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL


#ifndef __ASYNC_SYMUL_IMPL_HPP__
#define __ASYNC_SYMUL_IMPL_HPP__

#include "Physics.hpp"

#include <mutex>
#include <memory>
#include <thread>
#include <atomic>
#include <condition_variable>

// AsyncSymulImpl implement async calculation of point location
// MAIN THREAD: we set for which time we want value
// OTHER THREAD: get last time point and calculate location for it

class AsyncSymulImpl {
public:

    AsyncSymulImpl();
    ~AsyncSymulImpl();

    void start(Physics* physicPtr);
    void restart();
    void setWaitFor(float timeP);
    Point2d getLastReady() const;

private:

    float getLastWait() const;
    void setLastReady(const Point2d& point);
    void calcTreadFunc(Physics* physicPtr);
    void waitFinish();

private:

    std::unique_ptr<std::thread> asyncPtr;
    std::condition_variable conV;
    std::atomic<bool> isThreadExist;
    std::atomic<bool> isThisExist;
    mutable std::mutex dataM; // protect "readyP"
    Point2d readyP;
    Physics* activePhysic;
    float waiteFor;
};

#endif /* __ASYNC_SYMUL_IMPL_HPP__ */
