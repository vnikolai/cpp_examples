#include <iostream>

#include "thread_pool.hpp"

void print_thread_id()
{
    std::cout << "thread_id " << std::this_thread::get_id() << std::endl;
}


int main(int argc, const char** argv)
{
    thread_pool pool;

    for (int i = 0; i < 32; i++)
    {
        pool.push(std::function<void(void)>(print_thread_id));
    }

    pool.run();
    return 0;
}