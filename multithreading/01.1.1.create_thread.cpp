#include <iostream>
#include <thread>
#include <functional>

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

    std::function<void(void)> f(print_thread_id);
    std::thread t3(f);
    t3.join();

    print_thread_id();

    return 0;
}
