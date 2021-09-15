#include <iostream>
#include <map>
#include <tuple>

#define PRINT_FUNCTION std::cout << __PRETTY_FUNCTION__ << std::endl

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
void wrapper_simple(Args... args)
{
    PRINT_FUNCTION;
    func(args...);
}

int main(int argc, const char** argv)
{
    A a;
    wrapper_simple(a, std::move(a));

    return 0;
}