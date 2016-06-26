// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL


#include "AsyncSimulImpl.hpp"
#include "Logger.hpp"

#include <thread>
#include <cassert>
#include <mutex>

const char* MODULE_NAME = "Async";

AsyncSymulImpl::AsyncSymulImpl() :
    asyncPtr(nullptr),
    conV(),
    isThreadExist(false),
    isThisExist(true),
    dataM(),
    readyP(),
    activePhysic(nullptr),
    waiteFor(0.f) {
}

AsyncSymulImpl::~AsyncSymulImpl() {
    waitFinish();
}

void AsyncSymulImpl::waitFinish() {
    isThisExist.store(false);
    while(isThreadExist.load()) {
        // need for unlocking CV in calc thread
        waiteFor += 1.f;
        conV.notify_one();
    }
    isThisExist.store(true);
}

void AsyncSymulImpl::start(Physics* physicPtr) {
    assert(physicPtr != nullptr && "Invalid phyisc");
    activePhysic = physicPtr;
    Logger::info(MODULE_NAME, "Thread started.");
    if (asyncPtr != nullptr) {
        Logger::error(MODULE_NAME, "Already started one thread. Can't start new!");
        return;
    }
    isThreadExist.store(true);
    asyncPtr.reset(new std::thread(&AsyncSymulImpl::calcTreadFunc, this, activePhysic));
    asyncPtr->detach();
}

void AsyncSymulImpl::restart() {
    // mark that "this" deleted and wait while thread not finish
    // than start new tread
    assert(activePhysic != nullptr && "Noting to restart");
    waitFinish();
    asyncPtr.reset();
    activePhysic->reset();
    start(activePhysic);
}

void AsyncSymulImpl::calcTreadFunc(Physics* physicPtr) {
    float lastP = -1.f;
    while(isThisExist.load()) {
        std::unique_lock<std::mutex> tGuard(dataM);
        conV.wait(tGuard, [this, lastP](){
            return lastP < this->getLastWait();
        });
        float timeP = getLastWait();
        lastP = timeP;
        Point2d tPoint = physicPtr->getPointLoc(timeP);
        setLastReady(tPoint);
        if(physicPtr->isFinished()) {
            break;
        }
    }
    Logger::info(MODULE_NAME, "Thread finished.");
    isThreadExist.store(false);
}

float AsyncSymulImpl::getLastWait() const {
    return waiteFor;
}

void AsyncSymulImpl::setLastReady(const Point2d& point) {
    readyP = point;
}

Point2d AsyncSymulImpl::getLastReady() const {
    std::lock_guard<std::mutex> tGuard(dataM);
    return readyP;
}

void AsyncSymulImpl::setWaitFor(float timeP) {
    waiteFor = timeP;
    if(asyncPtr != nullptr && isThreadExist.load()) {
        conV.notify_one();
    } else if (asyncPtr != nullptr) {
        asyncPtr.reset();
    }
 }
