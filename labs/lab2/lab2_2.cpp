#include <iostream>

using namespace std;

class Car
{
public:
    string car_maker;
    string car_model;
    string car_year;
    int car_hp;

    Car(string carmaker, string model, string year, int hp);
    Car(string carmaker, string model, string year);
    Car(string carmaker, string model);
    Car(string model);
    Car()
    {
        car_maker = "default";
        car_model = "default";
        car_year = "default";
        car_hp = 0;
    }

    ~Car()
    {
        cout << "masina dusa la fier vechi" << endl;
    }
};

//"total" constructor
Car::Car(string maker, string model, string year, int hp)
{
    car_maker = maker;
    car_model = model;
    car_year = year;
    car_hp = hp;
}

Car::Car(string maker, string model, string year)
{
    car_maker = maker;
    car_model = model;
    car_year = year;
    car_hp = 0;
}

Car::Car(string maker, string model)
{
    car_maker = maker;
    car_model = model;
    car_year = "default";
    car_hp = 0;
}

Car::Car(string maker)
{
    car_maker = maker;
    car_model = "default";
    car_year = "default";
    car_hp = 0;
} 

int main()
{
    Car car1("VW", "Touran", "2004", 999);
    Car car2("BMW", "E36", "1995");
    Car car3("VW", "Passat");
    Car car4("Dacia");
    Car car5;

    cout << "Car 1: " << car1.car_maker << " " << car1.car_model << " " << car1.car_year << " " << car1.car_hp << endl;
    cout << "Car 2: " << car2.car_maker << " " << car2.car_model << " " << car2.car_year << " " << car2.car_hp << endl;
    cout << "Car 3: " << car3.car_maker << " " << car3.car_model << " " << car3.car_year << " " << car3.car_hp << endl;
    cout << "Car 4: " << car4.car_maker << " " << car4.car_model << " " << car4.car_year << " " << car4.car_hp << endl;
    cout << "Car 5: " << car5.car_maker << " " << car5.car_model << " " << car5.car_year << " " << car5.car_hp << endl;

    return 0;
}