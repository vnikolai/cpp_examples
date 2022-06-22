#include <iostream>
#include <thread>

#include <semaphore>

std::binary_semaphore semaphore{0};
bool quit = false;

int main(int argc, const char** argv)
{
    const int num_threads = 12;

    std::thread thread([]{
        while (!quit)
        {
            std::cout << "preparing new data block" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::cout << "notify semaphore" << std::endl;
            semaphore.release();
        }
    });

    while (!quit)
    {
        std::cout << "waiting for semaphore" << std::endl;
        semaphore.acquire();

        std::cout << "processing previous data block" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        //quit = true;
    }

    thread.join();

    return 0;
}
