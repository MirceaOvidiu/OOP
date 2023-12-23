#include <iostream>
#include <vector>

class Subscriber {
public:
    virtual void update(int value) = 0;
};

class ConcreteSubscriber : public Subscriber {
public:
    void update(int value) override {
        std::cout << "Concrete Subscriber was nofied with the value: " << value << std::endl;
    }
};

class Publisher {
private:
    std::vector<Subscriber*> Subscribers;
    int value;
public:
    void attach(Subscriber* Subscriber) {
        Subscribers.push_back(Subscriber);
    }

    void detach(Subscriber* Unsubscribed)
    {
        for (int i = 0; i < Subscribers.size(); i++)
        {
            if (Subscribers[i] == Unsubscribed)
            {
                Subscribers.erase(Subscribers.begin() + i);
                break;
            }
        }
    }

    void set_value(int new_value) {
        this->value = new_value;
        notify();
    }
    void notify() {
        for (Subscriber* Subscriber : Subscribers) {
            Subscriber->update(value);
        }
    }
};

int main() {
    Publisher Publisher;
    ConcreteSubscriber Subscriber1, Subscriber2;

    Publisher.attach(&Subscriber1);
    Publisher.attach(&Subscriber2);

    Publisher.set_value(10);
    return 0;
}

/*
pros/cons:
pro:
 - relatiile dintre functii si obiecte sunt foarte clare
 - se poate lucra intr-o maniera de tip "broadcast",
  unde orice actiune este monitorizata
  = se pot adauga oricand subscriberi

cons:
 - fara grija, se pot da update-uri nedorite
 - risc mare de memory leaks
 - complex
 - overkill pentru proiecte mici
*/