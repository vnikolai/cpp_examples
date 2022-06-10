#include <iostream>
#include <map>
#include <tuple>

#define PRINT_FUNCTION std::cout << FUNCTION_SIGNATURE << std::endl

struct A
{
    A() { PRINT_FUNCTION; }
    A(const A&) { PRINT_FUNCTION; }
    A(A&&) { PRINT_FUNCTION; }
};

template<typename... Args>
void func(Args... args)
{
    PRINT_FUNCTION;
}

template<typename... Args>
void wrapper_move(Args&&... args)
{
    PRINT_FUNCTION;
    func(std::move(args)...);
}

int main(int argc, const char** argv)
{
    A a;
    wrapper_move(a, std::move(a));

    return 0;
}