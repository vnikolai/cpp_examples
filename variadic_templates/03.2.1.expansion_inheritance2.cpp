#include <iostream>

template < typename T >
class variant_element
{
};

template < typename... Types >
class variant {
public:
    constexpr static size_t size = 0;
    void printHierarchy() {}
};

template < typename T, typename... Types >
class variant< T, Types... > : public variant_element<T>, public variant< Types... >
{
    using super = variant< Types... >;
public:
    constexpr static size_t size = std::max(sizeof(T), super::size);

    void printHierarchy()
    {
        std::cout << FUNCTION_SIGNATURE << std::endl;
        super::printHierarchy();
    }
};

int main(int argc, const char** argv)
{
    variant<int, double, char> v;
    v.printHierarchy();
    std::cout << v.size << std::endl;

    return 0;
}