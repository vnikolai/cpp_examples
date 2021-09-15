#include <iostream>
#include <map>
#include <tuple>

template <typename... Types> int func(Types... args)
{
    auto lambda = [args...](int a)
    {
        int sum = 0;
        ((sum += args * a), ...);
        return sum;
    };

    return lambda(5) + lambda(10);
}

int main(int argc, const char** argv)
{
    std::cout << func(1, 2, 3, 4, 5) << std::endl;

    return 0;
}