#include <iostream>
#include <string.h>

using namespace std;

class Sibling
{
public:
    string fname;
    string lname;
    int age;

    // default constructor
    Sibling()
    {
        fname = "Jon";
        lname = "Doe";
        age = 0;
    }

    ///default destructor
    ~Sibling();
};

Sibling::~Sibling()
{
    cout << "object destroyed" << endl;
}

int main()
{
    Sibling *sibling1 = new Sibling();

    sibling1->fname = "Ion";
    sibling1->lname = "Popescu";
    sibling1->age = 20;

    Sibling sibling2 = Sibling(*sibling1);
    sibling2.fname = "Ionut";
    sibling2.age = 21;

    cout << sibling1->fname << " " << sibling1->lname << " " << sibling1->age << endl;
    cout << sibling2.fname << " " << sibling2.lname << " " << sibling2.age << endl;

    delete sibling1;

    return 0;
}