#include <iostream>
#include <variant>
#include <vector>
#include <memory>

struct Node;

template<class... Ts> struct overloaded : Ts...
{
    using Ts::operator()...;
};

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

using attribute = std::variant<int, double, std::string, std::shared_ptr<Node>>;

struct Node
{
    std::vector<attribute> attributes;

    void print() const
    {
        std::cout << "{ ";
        for (auto attr : attributes)
        {
            std::visit(
                overloaded
                {
                    [](auto&& arg) { std::cout << arg; },
                    [](std::shared_ptr<Node>& node) { node->print(); },
                },
                attr);
            std::cout << " ";
        }
        std::cout << "}";
    }
};

int main(int argc, const char** argv)
{
    attribute a;
    a = 4;

    Node n;
    n.attributes.push_back(attribute(45));
    n.attributes.push_back("John");

    auto child = std::make_shared<Node>();
    child->attributes.push_back(17);
    child->attributes.push_back("Steven");

    n.attributes.push_back(child);

    n.print();

    std::cout << std::endl;

    return 0;
}