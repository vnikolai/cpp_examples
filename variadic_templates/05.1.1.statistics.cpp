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

    template <int N> void    
    print(const std::tuple<Args...>& tuple)
    {
        if constexpr (N > 0) // requires C++17
        {
            print<N - 1>(tuple);
            if constexpr (N > 1)
            {
                std::cout << ", ";
            }
            std::cout << std::get<N - 1>(tuple);
        }
    }

    void printTuple(const std::tuple<Args...>& tuple)
    {
        std::cout << "{ ";
        print<sizeof...(Args)>(tuple);
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