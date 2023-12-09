#include <iostream>
#include <cstdlib>

using namespace std;

class Money
{
private:
    int amount;

public:
    void set_amount()
    {
        amount = rand() % 100 + 1;
    }

    int get_amount()
    {
        return amount;
    }
};

int main()
{

    Money *money_ptr = new Money[3];

    for (int i = 0; i < 5; i++)
    {
        money_ptr[i].set_amount();
        cout << "amount of money " << money_ptr[i].get_amount() << "\n";
    }

    for (int i = 0; i < 5; i++)
    {
        if (money_ptr[i].get_amount() > 50)
        {
            cout << "amount of index " << i << " and of value " << money_ptr[i].get_amount() << " is greater than 50 \n ";
        }
    }

    return 0;
}