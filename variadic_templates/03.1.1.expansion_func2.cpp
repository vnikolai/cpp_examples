#include <iostream>

template<typename T>
void func(T value)
{
    std::cout << __PRETTY_FUNCTION__ << " " << value << std::endl; 
}

template <typename T, typename... Args>
void func(T value, Args... args)
{
    func(value);    
    func(args...);
}

int main(int argc, const char** argv)
{
    func(1, "mystring", 1.7);

    return 0;
}