#include <iostream>
#include <thread>

thread_local int counter = 0;

void increment_counter()
{
    counter = 10;
    std::cout << counter << std::endl;
}

int main(int argc, const char** argv)
{
    std::thread thread(increment_counter);
    thread.join();
    
    std::cout << counter << std::endl;

    return 0;
}
