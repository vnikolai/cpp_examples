#include <iostream>

// { Name, LastName }
// { Name, LastName, 1992 }

void serializeValues()
{
}

template <typename T> void serializeValue(const T& value)
{
    std::cout << value;
}

template <> void serializeValue<int>(const int& value)
{
    std::cout << "int : " << value;
}

void serializeValue(const char value[])
{
    std::cout << "string : " << value;
}

template <typename T, typename... Args> void serializeValues(const T& value, const Args&... args)
{
    serializeValue(value);
    std::cout << ", ";
    serializeValues(args...);
}

template <typename... Args> void serialize(const Args&... args)
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