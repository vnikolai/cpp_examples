#include <iostream>
#include <vector>
#include <algorithm>

void print(auto& vec)
{
    for (auto i : vec)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}

void without_erase()
{
    std::vector<int> vec{1, 2, 3, 2, 4, 5, 2};

    print(vec);

    std::remove_if(vec.begin(), vec.end(), [](const int& v)
    {
        return v == 2;
    });
    
    print(vec);
}

void with_erase()
{
    std::vector<int> vec{1, 2, 3, 2, 4, 5, 2};

    print(vec);

    vec.erase(std::remove_if(vec.begin(), vec.end(), [](const int& v)
    {
        return v == 2;
    }), vec.end());
    
    print(vec);
}

int main(int argc, const char** argv)
{
    without_erase();
    with_erase();

    return 0;
}
