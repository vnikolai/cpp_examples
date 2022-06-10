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

template<typename T>
void wrapper(T&& value)
{
    PRINT_FUNCTION;
    A(std::forward<T>(value));
}

int main(int argc, const char** argv)
{
    A a;
    
    wrapper(a);
    wrapper(std::move(a));

    return 0;
}