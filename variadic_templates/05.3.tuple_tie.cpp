#include <iostream>
#include <map>
#include <tuple>
#include <array>


int main(int argc, const char** argv)
{
    std::tuple<bool, int> t {true, 5};

    bool result;
    int value;

    std::tie(result, value) = t;

    std::cout << std::boolalpha << result << " "
              << value << std::endl;

    auto [r, v] = t; // Structured binding declaration C++17

    std::cout << std::boolalpha << r << " "
              << v << std::endl;

    std::map<int, int> m;
    auto [iterator, inserted] = m.emplace(5, 7);
    std::cout << inserted << " {" << iterator->first << " " << iterator->second << "}" << std::endl;

    return 0;
}