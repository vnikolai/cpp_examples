#include <iostream>
#include <thread>
#include <mutex>

const int num_tries = 1000000;
const int num_threads = 10;
const int num_iterations = 100;

int main(int argc, const char** argv)
{
    int nums_failed = 0;

    for (int i = 0; i < num_tries; i++)
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

        if (counter != num_threads * num_iterations)
        {
            std::cout << "Failed on " << i << " try with counter= " << counter << std::endl;
            nums_failed++;
        }

        std::cout << counter << " on try " << i << " failed " << nums_failed << std::endl;
    }

    std::cout << "nums_failed " << nums_failed << std::endl;

    return 0;
}
