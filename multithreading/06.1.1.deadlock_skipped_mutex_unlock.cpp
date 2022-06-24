#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mutex;

bool quit = false;

int main(int argc, const char** argv)
{
    std::thread thread([]{
        while (true)
        {
            mutex.lock();
            
            counter++;
            if (counter >= 10)
            {
                // quit = true;
                // uncommenting will reduce probability of deadlock 
                // and result in atexit abort with busy mutex dtor
                // if deadlock not hit
                break;
            }

            mutex.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });

    auto start = std::chrono::high_resolution_clock::now();

    while (!quit)
    {
        mutex.lock();

        std::cout << counter << std::endl;

        mutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    thread.join();

    return 0;
}
