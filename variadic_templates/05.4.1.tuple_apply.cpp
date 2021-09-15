#include <iostream>
#include <tuple>
#include <utility>

int sum(int a, int b)
{
    return a + b;
}

template <typename... Args> void print(Args... args)
{
    ((std::cout << args << " "), ...);
}

int main(int argc, const char** argv)
{
    std::tuple<int, int> t {3, 9};
    std::cout << std::apply(sum, t) << std::endl;

    std::apply(print<int, int>, t);

    std::cout << std::endl;

    return 0;
}