#include <iostream>
#include <stdio.h>
#include <string>

#define pi 3.141

using namespace std;

class Beer
{
protected:
    string type;
    string origin;

public:
    Beer(string type, string origin);
    Beer();
    string get_beer_type()
    {
        return this->type;
    }

    string get_beer_origin()
    {
        return this->origin;
    }

    void print_details()
    {
        std::cout << this->get_beer_type() << " din " << this->get_beer_origin() << "\n";
    }
};

Beer::Beer()
{
    this->type = "default";
    this->origin = "default";
}

// am folosit beer_type si beer_origin pentru a evita warningurile de shadowing
Beer::Beer(string beer_type, string beer_origin)
{
    this->type = beer_type;
    this->origin = beer_origin;
}

class Beer_square_label : public Beer
{
private:
    float label_length;

public:
    Beer_square_label();
    Beer_square_label(string type, string origin, float label_length);
    /// metodele care intorc tipul si originea
    /// sunt deja mostenite de la clasa Beer, nu
    /// au sens altele
    void print_details()
    {
        std::cout << this->get_beer_type() << " din " << this->get_beer_origin() << " cu aria etichetei de:" << this->label_area() << "\n";
    }

    float label_area()
    {
        return (this->label_length) * (this->label_length);
    }
};

Beer_square_label::Beer_square_label()
{
    this->origin = "default";
    this->type = "default";
    this->label_length = 0;
}

Beer_square_label::Beer_square_label(string beer_type, string beer_origin, float beer_label_length)
{
    this->type = beer_type;
    this->origin = beer_origin;
    this->label_length = beer_label_length;
}

class Beer_round_label : public Beer
{
private:
    double label_radius;

public:
    Beer_round_label();
    Beer_round_label(string type, string origin, double label_radius);

    double label_area()
    {
        return (pi * this->label_radius * this->label_radius);
    }

    void print_details()
    {
        std::cout << this->get_beer_type() << " din " << this->get_beer_origin() << " cu aria etichetei de:" << this->label_area() << "\n";
    }
};

Beer_round_label::Beer_round_label()
{
    this->type = "default";
    this->origin = "default";
    this->label_radius = 0;
}

Beer_round_label::Beer_round_label(string beer_type, string beer_origin, double beer_label_radius)
{
    this->type = beer_type;
    this->origin = beer_origin;
    this->label_radius = beer_label_radius;
}

class Beer_right_triangle_label : public Beer
{
private:
    float label_base;
    float label_heigth;

public:
    Beer_right_triangle_label();
    Beer_right_triangle_label(string type, string origin, float label_base, float label_heigth);

    double label_area()
    {
        return ((this->label_base) * (this->label_heigth) * 0.5);
    }

    void print_details()
    {
        std::cout << this->get_beer_type() << " din " << this->get_beer_origin() << " cu aria etichetei de:" << this->label_area() << "\n";
    }
};

Beer_right_triangle_label::Beer_right_triangle_label()
{
    this->type = "default";
    this->origin = "default";
    this->label_base = 0;
    this->label_heigth = 0;
}

Beer_right_triangle_label::Beer_right_triangle_label(string beer_type, string beer_origin, float beer_label_heigth, float beer_label_base)
{
    this->type = beer_type;
    this->origin = beer_origin;
    this->label_base = beer_label_base;
    this->label_heigth = beer_label_heigth;
}

int main()
{
    Beer Beer1 = Beer("Ciucas", "Rai");
    Beer_square_label Beer2 = Beer_square_label("Zaganu", "Bucuresti", 10);
    Beer_round_label Beer3 = Beer_round_label("Timisoreana", "Timisoara", 8);
    Beer_right_triangle_label Beer4 = Beer_right_triangle_label("Silva", "Transilvania", 8, 6);

    Beer1.print_details();
    Beer2.print_details();
    Beer3.print_details();
    Beer4.print_details();

    return 0;
}
