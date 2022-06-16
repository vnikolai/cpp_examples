#include <iostream>
#include <thread>
#include <vector>

using namespace std::chrono;

void average(const std::vector<int>& array, int start, int end, int& result)
{
    int64_t sum = 0;
    for (int i = start; i < end; ++i)
    {
        sum += array[i];
    }

    result = static_cast<int>(sum / (end - start));
}

int average_single_threaded(const std::vector<int>& array)
{
    int avg = 0;
    average(array, 0, array.size(), avg);
    return avg;
}

int average_multi_threaded(const std::vector<int>& array)
{
    const int num_threads = 2;
    const int step = array.size() / num_threads;

    std::thread threads[num_threads];
    int result[num_threads];

    for (int i = 0; i < num_threads; ++i)
    {
        threads[i] = std::thread(average, std::ref(array), i*step, (i + 1)*step, std::ref(result[i]));

        // threads[i] = std::thread([&array, i, &step, &result]() {
        //     average(array, i*step, (i + 1)*step, result[i]);
        //  });
    }

    int avg = 0;
    for (int i = 0; i < num_threads; ++i)
    {
        threads[i].join();
        avg += result[i];
    }

    return avg / num_threads;
}

int main(int argc, const char** argv)
{
    const int data_size = 1024*1024 * 256;
    std::vector<int> data(data_size);

    for (int i = 0; i < data_size; ++i)
    {
        data[i] = std::rand();
    }

    auto start_time = high_resolution_clock::now();

    int avg = average_single_threaded(data);

    auto end_time = high_resolution_clock::now();

    std::cout << "Singlethreaded: avg = " << avg << " time elapsed " << duration_cast<milliseconds>(end_time - start_time) << std::endl;

    start_time = high_resolution_clock::now();

    avg = average_multi_threaded(data);

    end_time = high_resolution_clock::now();

    std::cout << "Multithreaded: avg = " << avg << " time elapsed " << duration_cast<milliseconds>(end_time - start_time) << std::endl;

    return 0;
}
