#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

class DefaultClass
{
public:
    DefaultClass()
    {
        auto timenow =
            chrono::system_clock::to_time_t(chrono::system_clock::now());

        cout << "Object created at: " << ctime(&timenow) << endl;
    }

    ~DefaultClass()
    {
        auto timenow =
            chrono::system_clock::to_time_t(chrono::system_clock::now());

        cout << "Object destroyed at: " << ctime(&timenow) << endl;
    }
};

int main()
{
    DefaultClass MyClass = DefaultClass();

    return 0;
}