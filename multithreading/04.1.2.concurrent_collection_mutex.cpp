#include <iostream>
#include <thread>
#include <list>
#include <mutex>

bool quit = false;

std::list<int> data;
std::mutex mutex;

void calculate_thread()
{
    static int counter = 1;
    while (!quit)
    {
        ++counter;

        mutex.lock();

        data.push_back(counter);
        data.pop_front();

        mutex.unlock();
    }
}

void print_thread()
{
    int counter = 0;
    while (!quit)
    {
        mutex.lock();

        std::cout << "count = " << data.size() << std::endl;

        for (auto d : data)
        {
            std::cout << d << " ";
        }

        mutex.unlock();

        std::cout << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(int argc, const char** argv)
{
    data.push_back(1);

    std::jthread calc_thread(calculate_thread);

    print_thread();

    return 0;
}
