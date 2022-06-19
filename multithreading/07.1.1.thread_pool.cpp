#include <iostream>

#include "thread_pool.hpp"

std::mutex cout_mutex;

void print_thread_id()
{
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread_id " << std::this_thread::get_id() << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::microseconds(100));
}


int main(int argc, const char** argv)
{
    thread_pool pool;

    for (int i = 0; i < 128; i++)
    {
        pool.push(std::function<void(void)>(print_thread_id));
    }

    pool.run();
    return 0;
}