#include <iostream>
#include <thread>
#include <mutex>

const int num_threads = 10;
const int num_iterations = 100;

int main(int argc, const char** argv)
{
    int counter = 0;

    std::jthread threads[num_threads];

    for (int i = 0; i < num_threads; ++i)
    {
        threads[i] = std::jthread([&counter]{
            for (int i = 0; i < num_iterations; i++)
            {
                counter++;
            }
        });
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    std::cout << counter << std::endl;

    return 0;
}
