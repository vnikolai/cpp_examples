#include <iostream>
#include <thread>

bool quit = false;

auto fast = std::chrono::milliseconds(100);
auto slow = std::chrono::milliseconds(1000);
auto normal = std::chrono::milliseconds(250);

auto delay = normal;

void input_tread()
{
    while (!quit)
    {
        std::string input;
        std::cin >> input;

        if (input == "quit")
        {
            quit = true;
        } 
        else if (input == "fast")
        {
            delay = fast;
        }
        else if (input == "slow")
        {
            delay = slow;
        }
        else if (input == "normal")
        {
            delay = normal;
        }
    }
}

int main(int argc, const char** argv)
{
    std::thread input(input_tread);

    while (!quit)
    {
        std::cout << "working " << std::chrono::system_clock::now() << std::endl;
        std::this_thread::sleep_for(delay);
    }

    input.join();

    return 0;
}
