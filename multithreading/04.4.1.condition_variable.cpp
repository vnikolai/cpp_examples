#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;
std::condition_variable condition_variable;
bool data_ready = false;

int main(int argc, const char** argv)
{
    std::thread thread([]{
        // simulate smaller work
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::cout << "waiting for data" << std::endl;

        std::unique_lock lock(mutex);
        condition_variable.wait(lock, []{
            return data_ready;
        });
        lock.unlock();

        std::cout << "data is ready" << std::endl;
    });

    // simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    mutex.lock();
    data_ready = true;
    mutex.unlock();

    condition_variable.notify_one();

    thread.join();

    return 0;
}
