#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>

std::mutex mutex;
std::shared_mutex shared_mutex;

void simple()
{
    mutex.lock();
    // do job
    mutex.unlock();
}

void simple_with_lock()
{
    std::lock_guard<std::mutex> lock(mutex);
    // do job    
}

void partial()
{
    mutex.lock();
    // do job
    mutex.unlock();
    // cleanup
}

void partial_with_lock()
{
    std::unique_lock<std::mutex> lock(mutex);
    // do job
    lock.unlock();
    // cleanup
}

void shared()
{
    shared_mutex.lock_shared();
    // do job
    shared_mutex.unlock_shared();
}

void shared_with_lock()
{
    std::shared_lock<std::shared_mutex> lock(shared_mutex);
    // do job
}

void multiple()
{
    mutex.lock();
    shared_mutex.lock();
    // do job
    mutex.unlock();
    shared_mutex.unlock();
}

void multiple_with_lock()
{
    std::scoped_lock lock(mutex, shared_mutex);
    // do job
}

int main(int argc, const char** argv)
{    
    return 0;
}
