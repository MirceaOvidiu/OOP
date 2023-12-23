#include <iostream>
#include <vector>

///Composite

class Component
{
public:
    virtual void operation() const = 0;
    virtual ~Component() {}
};

class Leaf : public Component
{
public:
    void operation() const override
    {
        std::cout << "Leaf operation executed \n";
    }
};


class Composite : public Component
{
private:
    std::vector<Component *> children;

public:
    void add(Component *component)
    {
        children.push_back(component);
    }

    void operation() const override
    {
        std::cout << "Composite operation executed.\nChildren:\n";
        for (const Component *c : children)
        {   
            c->operation();
        }
    }

    ~Composite()
    {
        for (Component *child : children)
        {
            delete child;
        }
    }
};

int main()
{
    Composite *composite = new Composite();
    composite->add(new Leaf());
    composite->add(new Leaf());
    composite->operation(); 
    delete composite;
    return 0;
}

/*pros and cons
pro:
 - structura ierarhica a codului este usor de urmarit
 - ofera o clasificare buna a functiilor si obictelor, in functie de scopul lor
 - usor de scalat
 - usor de modificat in mod dinamic

cons:
 - overhead in folosirea unui obiect/functii, fiind neceaara parcurgerea arborelui
 - overuse
 - fara grija, modificarea unui composite sau component poate afecta toate componentele
 de dedesubt.
*/