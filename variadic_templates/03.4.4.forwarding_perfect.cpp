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
void wrapper_forwarding(Args&&... args)
{
    PRINT_FUNCTION;
    func(std::forward<Args>(args)...);
}

int main(int argc, const char** argv)
{
    A a;
    wrapper_forwarding(a, std::move(a));
    
    return 0;
}