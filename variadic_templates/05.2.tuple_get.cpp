#include <iostream>
#include <array>
#include <tuple>


int main(int argc, const char** argv)
{
    std::tuple<int, int, int> t {3, 4, 5};

    std::get<2>(t) = 7;

    std::cout << std::get<0>(t) << " "
              << std::get<1>(t) << " "
              << std::get<2>(t) << std::endl;

    std::pair<float, float> p {2.2, 3.7};
    std::cout << std::get<1>(p) << std::endl;

    std::array<float, 3> a {2.2, 3.7, 4.4};
    std::cout << std::get<2>(a) << std::endl;

    return 0;
}