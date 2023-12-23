#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Salad {
public:
    string name;
    vector<string> ingredients;

    void listIngredients() {
        cout << "Salad Ingredients:" << endl;
        for (auto& ingredient : ingredients) {
            cout << ingredient << endl;
        }
    }
};

class SaladBuilder {
protected:
    Salad* salad;
public:
    SaladBuilder() { this->salad = new Salad(); }
    virtual ~SaladBuilder() { delete this->salad; }

    virtual void nameSalad() = 0;
    virtual void addLettuce() = 0;
    virtual void addTomato() = 0;
    virtual void addCheese() = 0;
    virtual void addDressing() = 0;

    Salad* getSalad() { return this->salad; }
};

class CaesarSaladBuilder : public SaladBuilder {
public:
    void nameSalad() override { this->salad->name = "Caesar Salad"; }
    void addLettuce() override { this->salad->ingredients.push_back("Lettuce"); }
    void addTomato() override { this->salad->ingredients.push_back("Tomato"); }
    void addCheese() override { this->salad->ingredients.push_back("Cheese"); }
    void addDressing() override { this->salad->ingredients.push_back("Caesar Dressing"); }
};

class Director {
public:
    Salad* makeSalad(SaladBuilder* builder) {
        builder->nameSalad();
        builder->addLettuce();
        builder->addTomato();
        builder->addCheese();
        builder->addDressing();
        return builder->getSalad();
    }
};

int main() {
    Director director;
    CaesarSaladBuilder builder;
    Salad* salad = director.makeSalad(&builder);
    std::cout << "Salad name: " << salad->name << std::endl;
    salad->listIngredients();
    delete salad;
    return 0;
}

/*
pro:
- constrol extensiv in crearea obiectelor
- creare pas cu pas a obiectelor
- flexibilitate in crearea obiectelor

contra:
- potential aspect oribil al constructorului
- cod redundant

*/

