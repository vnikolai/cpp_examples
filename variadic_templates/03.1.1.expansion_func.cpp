#include <iostream>

void func()
{
}

template <typename T, typename... Args>
void func(T value, Args... args)
{
    std::cout << FUNCTION_SIGNATURE << std::endl;
    std::cout << " " << value << std::endl;
    
    func(args...);
}

int main(int argc, const char** argv)
{
    func(1, "string", 1.7);

    return 0;
}