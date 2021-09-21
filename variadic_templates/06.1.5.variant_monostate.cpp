#include <iostream>
#include <variant>

int main(int argc, const char** argv)
{
    std::variant<int, float> vif;

    std::cout << "Defaunt constructed int " 
              << std::boolalpha << std::holds_alternative<int>(vif)
              << std::endl;
    
    std::variant<std::monostate, int, float> vmif;

    std::cout << "Constructed with monostate contains int " 
              << std::boolalpha << std::holds_alternative<int>(vmif)
              << std::endl;

    vmif = 4;

    std::cout << "Pushed int contains int " 
              << std::boolalpha << std::holds_alternative<int>(vmif)
              << std::endl;

    vmif = std::monostate();

    std::cout << "Pushed monostate contains int " 
              << std::boolalpha << std::holds_alternative<int>(vmif)
              << std::endl;

    return 0;
}