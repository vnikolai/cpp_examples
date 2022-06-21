#include <iostream>
#include <thread>
#include <map>

std::map<int, std::string> data;
bool quit = false;

void calculate_thread()
{
    static int counter = 1;
    while (!quit)
    {
        ++counter;
        auto inserted = data.emplace(counter, "text");
        data.erase(inserted.first);
    }
}

void print_thread()
{
    int counter = 0;
    while (!quit)
    {
        for (auto d : data)
        {
            std::cout << d.first << " " << d.second << " ";
        }

        std::cout << std::endl;
    }
}

int main(int argc, const char** argv)
{
    std::jthread calc_thread(calculate_thread);

    print_thread();

    return 0;
}
