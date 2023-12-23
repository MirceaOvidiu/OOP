#include <iostream>

using namespace std;

class Plane
{
public:
    virtual void printInfo() = 0;
    virtual ~Plane() = default;
};

class Boeing747 : public Plane
{
public:
    Boeing747()
    {
        cout << "747 assembled" << endl;
    }

    void printInfo() override
    {
        cout << "Top Speed: Mach 0.9, Wingspan: 36m" << endl;
    }
};

class Cessna : public Plane
{
public:
    Cessna()
    {
        cout << "Cessna assembled" << endl;
    }

    void printInfo() override
    {
        cout << "Top Speed: 400km/h, Wingspan: 11m" << endl;
    }
};

class F16 : public Plane
{
public:
    F16()
    {
        cout << "F16 assembled" << endl;
    }

    void printInfo() override
    {
        cout << "Top Speed: Mach 2.0, Wingspan: 10m" << endl;
    }
};

class BoeingFactory
{
public:
    virtual Plane *make747() = 0;
    virtual Plane *makeCessna() = 0;
    virtual Plane *makeF16() = 0;
    virtual ~BoeingFactory() = default;
};

class Boeing747Factory : public BoeingFactory
{
public:
    Plane *make747() override
    {
        return new Boeing747();
    }

    Plane *makeCessna() override
    {
        return nullptr;
    }

    Plane *makeF16() override
    {
        return nullptr;
    }
};

class CessnaFactory : public BoeingFactory
{
public:
    Plane *make747() override
    {
        return nullptr;
    }

    Plane *makeCessna() override
    {
        return new Cessna();
    }

    Plane *makeF16() override
    {
        return nullptr;
    }
};

class F16Factory : public BoeingFactory
{
public:
    Plane *make747() override
    {
        return nullptr;
    }

    Plane *makeCessna() override
    {
        return nullptr;
    }

    Plane *makeF16() override
    {
        return new F16();
    }
};

int main()
{
    BoeingFactory *factory = new Boeing747Factory();
    Plane *plane = factory->make747();
    plane->printInfo();
    delete plane;
    delete factory;

    factory = new CessnaFactory();
    plane = factory->makeCessna();
    plane->printInfo();
    delete plane;
    delete factory;

    factory = new F16Factory();
    plane = factory->makeF16();
    plane->printInfo();
    delete plane;
    delete factory;

    return 0;
}

/*pro
- consistenta
- obicetele asemanatoare se pot crea usor
- reutizabilitate mare

Contra:
- complexitate mare
- risc de overhead -> bottleneck

*/