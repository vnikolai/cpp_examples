#include <iostream>

template < typename Signature >
class Functor;

template < typename Ret, typename... Args >
class Functor< Ret( Args... ) >
{
};

int main(int argc, const char** argv)
{
    Functor <void()>();
    Functor <void(int, float)>();

    return 0;
}