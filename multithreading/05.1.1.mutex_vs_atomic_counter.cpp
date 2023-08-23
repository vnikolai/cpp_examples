#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::chrono;

const int limit = 1024 * 1024 * 128;
const int num_threads = 12;
const bool simulate_work = false;
const bool logging = false;
const auto sleep_duration = std::chrono::nanoseconds(100);

void counter_with_mutex()
{
    bool end = false;
    std::mutex counter_mutex;
    int counter = 0;

    std::jthread threads[num_threads];

    for (int i = 0; i < num_threads; ++i)
    {
        threads[i] = std::jthread([&counter, &counter_mutex, &end]{
            while (!end)
            {
                if (simulate_work)
                {
                    std::this_thread::sleep_for(sleep_duration);
                }

                counter_mutex.lock();
                counter++;
                counter_mutex.unlock();
            }
        });
    }

    while (!end)
    {
        counter_mutex.lock();
        if (counter >= limit)
        {
            end = true;
        }

        counter_mutex.unlock();
        
        if (logging)
        {
            std::cout << counter << std::endl;
        }        
    }
}

void counter_with_atomic_operation()
{
    bool end = false;
    std::atomic<int> counter = 0;

    std::jthread threads[num_threads];

    for (int i = 0; i < num_threads; ++i)
    {
        threads[i] = std::jthread([&counter, &end]{
            while (!end)
            {
                if (simulate_work)
                {
                    std::this_thread::sleep_for(sleep_duration);
                }
                counter++;
            }
        });
    }

    while (!end)
    {
        int count = counter;
        if (count >= limit)
        {
            end = true;
        }

        if (logging)
        {
            std::cout << count << std::endl;
        }
    }
}

int main(int argc, const char** argv)
{
    auto start_time = high_resolution_clock::now();

    counter_with_mutex();

    auto end_time = high_resolution_clock::now();

    std::cout << "counter_with_mutex() time elapsed " << duration_cast<milliseconds>(end_time - start_time) << std::endl;


    start_time = high_resolution_clock::now();

    counter_with_atomic_operation();

    end_time = high_resolution_clock::now();

    std::cout << "counter_with_atomic_operation() time elapsed " << duration_cast<milliseconds>(end_time - start_time) << std::endl;
    

    return 0;
}
