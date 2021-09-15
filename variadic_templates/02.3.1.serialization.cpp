#include <iostream>

// { Name, LastName }
// { Name, LastName, 1992 }

void serializeValues()
{
}

template <typename T> void serializeValues(T value)
{
    std::cout << value;
}

template <typename T, typename... Args> void serializeValues(T value, Args... args)
{
    std::cout << value << ", ";
    serializeValues(args...);
}

template <typename... Args> void serialize(Args... args)
{
    std::cout << "{ " ;
    serializeValues(args...);
    std::cout << " }" << std::endl ;
};

int main(int argc, const char** argv)
{
    serialize("Name", "LastName");
    serialize("Name", "LastName", 1992);

    std::cout << std::endl;

    return 0;
}