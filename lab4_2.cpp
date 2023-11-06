#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

/*desi poate pare un exemplu banal, consider ca
aratand mostenirea unor caracteristicim ale 
copilului, atat de la mama cat si de tata,
este ilustrat bine conceptul de mostenire
multipla*/

class Father
{
public:
    string father_last_name;
    string father_eye_color;
    string father_hair_color;
    int father_height;

    Father(string lastname, string eye_color, string hair_color, int father_height);
};

Father::Father(string lastname, string eye_color, string hair_color, int height)
{
    this->father_last_name = lastname;
    this->father_eye_color = eye_color;
    this->father_hair_color = hair_color;
    this->father_height = height;
}

class Mother
{
public:
    string mother_last_name;
    string mother_eye_color;
    string mother_hair_color;
    int mother_height;

    Mother(string mother_last_name, string mother_eye_color, string mother_hair_color, int mother_height);
};

Mother::Mother(string lastname, string eye_color, string hair_color, int height)
{
    this->mother_last_name = lastname;
    this->mother_eye_color = eye_color;
    this->mother_hair_color = hair_color;
    this->mother_height = height;
}

class Child : public Father, public Mother
{
public:
    Child()
        : Father("default_father_last_name", "blue", "brown", 180),
          Mother("Smith", "default_mother_eye_color", "default_mother_hair_color", 170)
    {
        this->father_last_name = Father::father_last_name;
        this->mother_eye_color = Mother::mother_eye_color;
        this->mother_hair_color = Mother::mother_hair_color;
        this->father_height = (Father::father_height + Mother::mother_height) / 2;
    }

    void print_fields()
    {
        cout << "last name: " << father_last_name << endl;
        cout << "eye color: " << mother_eye_color << endl;
        cout << "color: " << mother_hair_color << endl;
        cout << "height: " << father_height << endl;
    }
};
int main()
{
    Father father("Smith", "blue", "brown", 180);
    Mother mother("Doe", "blue", "brown", 170);
    Child child;
    child.print_fields();

    return 0;
}
