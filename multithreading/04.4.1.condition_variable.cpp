#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;
std::condition_variable condition_variable;
bool data_ready = false;

int main(int argc, const char** argv)
{
    std::jthread thread([]{
        std::cout << "waiting for data" << std::endl;

        std::unique_lock lock(mutex);
        condition_variable.wait(lock, []{return data_ready;});
        lock.unlock();

        std::cout << "data is ready" << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    data_ready = true;
    condition_variable.notify_one();

    return 0;
}
