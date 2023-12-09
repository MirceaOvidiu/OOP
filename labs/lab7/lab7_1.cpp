#include <iostream>
#include <string>
#include <string.h>

using namespace std;

template <typename X>
X concat(X a, X b)
{
    return a + b;
}

template <>
int concat(int a, int b)
{
    return 10 * a + b;
}

string concat(string a, string b)
{
    return a + b;
}

int main()
{
    cout << concat(1, 2) << endl;
    cout << concat<string>("a\0","b\0") << endl;
    cout << concat<string>("fanta", "stik") << endl;

    return 0;
}