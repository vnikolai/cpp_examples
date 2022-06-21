#include <iostream>
#include <thread>
#include <future>

int main(int argc, const char** argv)
{
    std::packaged_task<int()> task([]{
        return std::rand();
    });

    std::future<int> future_task = task.get_future();
    std::jthread thread_task(std::move(task));

    std::cout << future_task.get(); // waits and returns value
    std::cout << std::endl;

    std::future<int> future_async = std::async(std::launch::async, []{
        return std::rand();
    });

    std::cout << future_async.get(); // waits and returns value
    std::cout << std::endl;

    std::promise<int> promise;
    std::future<int> future_promise = promise.get_future();

    std::jthread thread_promise([&promise]{
        promise.set_value(std::rand());
    });

    std::cout << future_promise.get(); // waits and returns value
    std::cout << std::endl;

    return 0;
}
