#include <iostream>
#include <tuple>
#include <utility>

template <typename... Args> void print(Args... args)
{
    ((std::cout << args << " "), ...);
}

template <typename... Args> void print_tuple(std::tuple<Args...> tuple)
{
    std::apply(print<Args...>, tuple);
}

int main(int argc, const char** argv)
{
    std::tuple<int, int> t {3, 9};
    print_tuple(t);

    return 0;
}