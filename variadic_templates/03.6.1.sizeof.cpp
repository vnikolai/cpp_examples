#include <iostream>
#include <map>
#include <tuple>

template <typename... Types> int size()
{
    return sizeof...(Types);
}

int main(int argc, const char** argv)
{
    std::cout << size<int, float>() << std::endl;
    std::cout << size<int, float, char>() << std::endl;

    std::tuple<char, char, float, float> t;
    std::cout << std::tuple_size<decltype(t)>{} << std::endl;

    return 0;
}