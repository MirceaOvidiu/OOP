#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Country
{
public:
    virtual void print_name() = 0;
    virtual void print_capital() = 0;
    virtual void print_favourite_food() = 0;

    void print_country_details()
    {
        print_name();
        print_capital();
        print_favourite_food();
        std::cout << "\n";
    }
};

class Romania : public Country
{
public:
    void print_name()
    {
        std::cout << "Romania\n";
    }

    void print_capital()
    {
        std::cout << "Bucharest\n";
    }

    void print_favourite_food()
    {
        std::cout << "Sarmale\n";
    }
};

class France : public Country
{
    public:
    void print_name()
    {
        std::cout << "France\n";
    }

    void print_capital()
    {
        std::cout << "Paris\n";
    }

    void print_favourite_food()
    {
        std::cout << "Escargot\n";
    }
};

class Germany : public Country
{
    public:
    void print_name()
    {
        std::cout << "Deutschland\n";
    }

    void print_capital()
    {
        std::cout << "Berlin\n";
    }

    void print_favourite_food()
    {
        std::cout << "Sauerkraut\n";
    }
};

int main()
{
    Romania ro;
    France fr;
    Germany de;

    ro.print_country_details();
    fr.print_country_details();
    de.print_country_details();

    return 0;
}