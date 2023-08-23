#include <iostream>
#include <thread>
#include <stop_token>

void infinite_loop(std::stop_token token)
{
    int counter = 0;

    while (!token.stop_requested())
    {
        ++counter;
        std::cout << counter << std::endl;
    }
}

int main(int argc, const char** argv)
{
    std::jthread t(infinite_loop);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    t.request_stop();

    return 0;
}
