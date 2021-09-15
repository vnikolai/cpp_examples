#include <iostream>
#include <map>
#include <tuple>

template<typename... Args>
class statistics
{
public:
    void record(const Args&... args)
    {
        auto record = count.emplace(
                                std::make_pair(
                                    std::make_tuple(args...),
                                    0));
        record.first->second++;
    }

    template <typename T> static void printArguments(const T& t)
    {
        std::cout << t;
    }

    template <typename T, typename... Args2> static void 
    printArguments(const T& t, Args2... args)
    {
        printArguments(t);
        std::cout << ", ";
        printArguments(std::forward<Args2>(args)...) ;
    }

    static void 
    print(Args... args)
    {
        printArguments(std::forward<Args>(args)...);
    }
    
    void printTuple(std::tuple<Args...> tuple)
    {
        std::cout << "{ ";
        std::apply(print, tuple);
        std::cout << " }";
    }

    void log()
    {
        for (auto record : count)
        {
            std::cout << "Entry with data ";
            printTuple(record.first);
            
            std::cout << " occured " << record.second << " times"<< std::endl;
        }
    }

private:

    std::map<std::tuple<Args...>, int> count;
};

statistics<int> myStatistics;
statistics<float, float> myOtherStatistics;

void myFunc(int i)
{
    myStatistics.record(i);
}

void myOtherFunc(float f1, float f2)
{
    myOtherStatistics.record(f1, f2);
}

int main(int argc, const char** argv)
{
    myFunc(1);
    myFunc(1);
    myFunc(2);
    myFunc(3);

    myStatistics.log();

    myOtherFunc(1, 2);
    myOtherFunc(1, 3);
    myOtherFunc(1, 3);
    myOtherFunc(2, 3);
    myOtherFunc(3, 4);

    myOtherStatistics.log();

    return 0;
}