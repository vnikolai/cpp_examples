#include <iostream>
#include <variant>
#include <map>

using attribute = std::variant<int, double, std::string>;

struct Node
{
    std::map<std::string, attribute> attributes;
    std::map<std::string, Node> children;

    void print()
    {
        std::cout << "< ";
        for (auto pair : attributes)
        {
            std::cout << pair.first << "=";
            std::visit( [](auto&& arg) { std::cout << arg; }, pair.second);
            std::cout << " ";
        }
        std::cout << ">";

        std::cout << std::endl;

        for (auto pair : children)
        {
            std::cout << '\t' << "< " << pair.first << " >";
            pair.second.print();
        }
    }
};

int main(int argc, const char** argv)
{
    attribute a;
    a = 4;

    Node n;
    n.attributes.emplace("age", 45);
    n.attributes.emplace("name", "John");

    Node child;
    child.attributes.emplace("age", 17);
    child.attributes.emplace("name", "Steven");
    n.children.emplace("son", child);

    n.print();

    std::cout << std::endl;

    return 0;
}