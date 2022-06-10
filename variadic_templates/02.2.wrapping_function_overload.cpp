#include <iostream>

bool validate(int i)
{
    std::cout << "validating int " << i << std::endl;
    return false;
};

bool validate(float f, char c)
{
    std::cout << "validating float, char " << f << " " << c <<  std::endl;
    return true;
};

void process(int)
{
    std::cout << "processing int" << std::endl;
};

void process(float, char)
{
    std::cout << "processing char, float" << std::endl;
};

template <typename... Args> void handler(Args... args)
{
    if (validate(args...))
    {
        process(args...);
    }
};

int main(int argc, const char** argv)
{
    handler(5);
    handler(0.7f, 'a');

    std::cout << std::endl;

    return 0;
}