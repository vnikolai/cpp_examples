#include <iostream>
#include <thread>
#include <mutex>

std::mutex cout_mutex;

int main(int argc, const char** argv)
{
    const int num_threads = 12;

    std::jthread threads[num_threads];

    for (int i = 0; i < num_threads; ++i)
    {
        threads[i] = std::jthread([]{
            while (true)
            {
                cout_mutex.lock();
                std::cout << "Hello " << "multithreading " << "world!!! " << std::this_thread::get_id() << std::endl;
                cout_mutex.unlock();
                
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        });
    }

    return 0;
}
