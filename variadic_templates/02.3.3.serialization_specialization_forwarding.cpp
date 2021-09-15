#include <iostream>

// { Name, LastName }
// { Name, LastName, 1992 }

void serializeValues()
{
}

template <typename T> void serializeValue(T&& value)
{
    std::cout << value;
}

template <> void serializeValue<int>(int&& value)
{
    std::cout << "int : " << value;
}

template <> void serializeValue<const char*>(const char* && value)
{
    std::cout << "string : " << value;
}

template <typename T, typename... Args> void serializeValues(T&& value, Args&&... args)
{
    serializeValue(std::forward<T>(value));
    std::cout << ", ";
    serializeValues(std::forward<Args>(args)...);
}

template <typename... Args> void serialize(Args... args)
{
    std::cout << "{ " ;
    serializeValues(std::forward<Args>(args)...);
    std::cout << " }" << std::endl ;
};

int main(int argc, const char** argv)
{
    serialize("Name", "LastName");
    serialize("Name", "LastName", 1992);

    std::cout << std::endl;

    return 0;
}