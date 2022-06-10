#include <iostream>

struct A
{
    template< typename... Args > A(Args...) { std::cout << FUNCTION_SIGNATURE << std::endl; }
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
    f.construct(1.1f, 1.2f);
    f.construct("mystring");

    return 0;
}