#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

class Volume
{
public:
    void compute_volume()
    {
        std::cout << "volume succesfully calculated: ";
    }

    int compute_volume(int length)
    {
        compute_volume();
        return static_cast<int>(pow(length, 3));
        //daca as fi pus fara cast:
        //conversion from '__gnu_cxx::__promote<double>::__type' {aka 'double'} to 'int' may change value [-Wfloat-conversion]
    }

    double compute_volume(double radius)
    {   
        compute_volume();
        return 4 * M_PI * pow(radius, 3) / 3;
    }

    // nu apar probleme pentru ca parametrii sunt 2 double-uri
    double compute_volume(double base_length, double height)
    {   
        compute_volume();
        return pow(base_length, 2) * height / 3;
    }
};

int main()
{
    Volume v;
    cout << v.compute_volume(2) << endl;
    cout << std::fixed << v.compute_volume(2.0) << endl;
    cout << v.compute_volume(2.0, 3.0) << endl;
    return 0;
}