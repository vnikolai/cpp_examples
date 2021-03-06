#include <iostream>
#include <thread>
#include <functional>

void print_thread_id()
{
    std::cout << "thread_id " << std::this_thread::get_id() << std::endl;
}

int main(int argc, const char** argv)
{
    std::jthread t(print_thread_id);

    std::jthread t2(
        [](){
            print_thread_id();
        });

    std::function<void(void)> f(print_thread_id);
    std::jthread t3(f);

    print_thread_id();

    return 0;
}
