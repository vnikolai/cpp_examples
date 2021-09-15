#include <iostream>
#include <map>

// does not work with POD types

template < typename... Types >
class variant : Types...
{
    using Types::operator[]...;
};

int main(int argc, const char** argv)
{
    variant<std::map<int, int>, std::string> v;

    std::cout << (std::string&)v;
    
    return 0;
}