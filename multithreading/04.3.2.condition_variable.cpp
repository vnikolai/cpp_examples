#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable condition_variable;
bool job_done = false;

int main(int argc, const char** argv)
{
    std::thread thread([]{
        // simulate some work
        std::this_thread::sleep_for(std::chrono::seconds(1));

        mutex.lock();
        job_done = true;
        mutex.unlock();

        condition_variable.notify_one();

        std::cout << "job is done, cleaning up" << std::endl;
    });

    std::cout << "waiting for data" << std::endl;

    // simulate smaller work
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::unique_lock lock(mutex);
    condition_variable.wait(lock, []{
        return job_done;
    });
    lock.unlock();

    std::cout << "finishing" << std::endl;

    thread.join();

    

    return 0;
}
