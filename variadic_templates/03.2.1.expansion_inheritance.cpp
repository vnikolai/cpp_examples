#include <iostream>

template < typename... Types >
class tuple;

template <>
class tuple <>
{
public:
    void checkHierarchy() { };
};

template < typename T, typename... Types >
class tuple< T, Types... > : public tuple< Types... >
{
    using super = tuple< Types... >;
public:
    void checkHierarchy()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        super::checkHierarchy();
    }
};

int main(int argc, const char** argv)
{
    tuple<int, int, double, char> v;

    v.checkHierarchy();

    return 0;
}