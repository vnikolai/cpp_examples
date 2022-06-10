#include <iostream>
#include <thread>

void infinite_loop()
{
    int counter = 0;

    while (true)
    {
        ++counter;
        std::cout << counter << std::endl;
    }
}

int main(int argc, const char** argv)
{
    std::thread t(infinite_loop);
    t.detach();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
