#include <iostream>

struct A
{
    template< typename... Args > A(Args...) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

struct Factory
{
    A construct(int i)
    {
        return A(i);
    }

    A construct(float f1, float f2)
    {
        return A(f1, f2);
    }

    A construct(const char* str)
    {
        return A(str);
    }
};

int main(int argc, const char** argv)
{
    Factory f;
    f.construct(1);
    f.construct(1.1, 1.2);
    f.construct("mystring");

    return 0;
}