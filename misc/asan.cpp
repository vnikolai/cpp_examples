// compile with
// add_compile_options(-fsanitize=address)
// add_compile_options(-fsanitize-recover=address)
// add_link_options(-fsanitize=address)
//
// run with ASAN_OPTIONS=halt_on_error=false

#include <iostream>

void error1()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    
    char array[1024];

    for (int i = 0; i < 1024 + 10; ++i)
    {
        std::cout << array[i] << " ";
    }

}

void error2()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    float array[1024];

    for (int i = 0; i < 1024 + 10; ++i)
    {
        std::cout << array[i] << " ";
    }
}


int main(int argc, const char** argv)
{
    error1();
    error2();

    return 0;
}
