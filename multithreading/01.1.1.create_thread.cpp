#include <iostream>
#include <thread>

void print_thread_id()
{
    std::cout << "thread_id " << std::this_thread::get_id() << std::endl;
}

int main(int argc, const char** argv)
{
    std::thread t(print_thread_id);
    t.join();

    std::thread(
        [](){
            print_thread_id();
        }).join();

    print_thread_id();

    return 0;
}
