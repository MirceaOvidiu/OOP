#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

/*desi poate pare un exemplu banal, consider ca
aratand mostenirea unor caracteristicim ale 
copilului, atat de la mama cat si de tata,
este ilustrat bine conceptul de mostenire
multipla*/

class Father {
public:
    string father_last_name;
    string father_eye_color;
    string father_hair_color;
    int father_height;

    Father(string lastname, string eye_color, string hair_color, int father_height);
};

Father::Father(string lastname, string eye_color, string hair_color, int height) {
    this->father_last_name = lastname;
    this->father_eye_color = eye_color;
    this->father_hair_color = hair_color;
    this->father_height = height;
}

class Mother {
public:
    string mother_last_name;
    string mother_eye_color;
    string mother_hair_color;
    int mother_height;

    Mother(string mother_last_name, string mother_eye_color, string mother_hair_color, int mother_height);
};

Mother::Mother(string lastname, string eye_color, string hair_color, int height) {
    this->mother_last_name = lastname;
    this->mother_eye_color = eye_color;
    this->mother_hair_color = hair_color;
    this->mother_height = height;
}

class Child : public Father, public Mother {
public:
    double height;

    Child(string father_ln, string father_eye, string father_hair, int father_h,
          string mother_ln, string mother_eye, string mother_hair, int mother_h)
        : Father(father_ln, father_eye, father_hair, father_h),
          Mother(mother_ln, mother_eye, mother_hair, mother_h),
          height((static_cast<double>(father_h) + static_cast<double>(mother_h)) / 2.0)
    {
    }

    void print_fields() {
        cout << "last name: " << father_last_name << endl;
        cout << "eye color: " << mother_eye_color << endl;
        cout << "hair color: " << mother_hair_color << endl;
        cout << "height: " << this->height << endl;
    }
};
int main() {
    Father father("Smith", "blue", "brown", 180);
    Mother mother("Doe", "green", "blonde", 170);
    Child child("Smith", "blue", "brown", 180,
                "Doe", "green", "blonde", 170);
    child.print_fields();

    return 0;
}