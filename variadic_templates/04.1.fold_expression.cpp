#include <iostream>
#include <vector>

template <typename... Args> auto sum(Args... args)
{
    return (args + ...);
    //return (... + args);
};

template <typename... Args> void func(Args... args)
{
    ((std::cout << args << " "), ...);
};

template <typename V, typename... Args> void push_back(V& vector, Args... args)
{
    (..., vector.push_back( args ));
};


int main(int argc, const char** argv)
{
    std::cout << sum(1, 2, 3, 4, 5) << std::endl;
    // expands to (1 + (2 + (3 + (4 + 5))))

    func(5, 0.7, 'a');

    std::cout << std::endl;

    std::vector<int> vec;
    push_back(vec, 1, 4, 7);

    for (auto i : vec)
    {
        std::cout << i << " ";
    }

    return 0;
}