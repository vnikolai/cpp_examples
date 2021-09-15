#include <iostream>
#include <variant>
#include <map>
#include <memory>

struct Node;

using attribute = std::variant<int, double, std::string, std::shared_ptr<Node>>;

struct Node
{
    std::map<std::string, attribute> attributes;

    struct printer
    {
        template <typename T> void operator()(T& arg) { std::cout << arg; }
        void operator()(std::shared_ptr<Node>& node) { node->print(); }
    };

    void print() const
    {
        std::cout << "{ ";
        for (auto pair : attributes)
        {
            std::cout << pair.first << ":";
            std::visit(printer(), pair.second);
            std::cout << ", ";
        }
        std::cout << "}";
    }
};

int main(int argc, const char** argv)
{
    attribute a;
    a = 4;

    Node n;
    n.attributes.emplace("age", 45);
    n.attributes.emplace("name", "John");

    auto child = std::make_shared<Node>();
    child->attributes.emplace("age", 17);
    child->attributes.emplace("name", "Steven");

    n.attributes.emplace("son", child);

    n.print();

    std::cout << std::endl;

    return 0;
}