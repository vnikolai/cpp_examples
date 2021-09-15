#include <iostream>

template < typename Signature >
class Functor;

template < typename Ret, typename... Args >
class Functor< Ret( Args... ) >
{
};

int main(int argc, const char** argv)
{
    Functor <void()> f;
    Functor <void(int, float)> f2;

    return 0;
}