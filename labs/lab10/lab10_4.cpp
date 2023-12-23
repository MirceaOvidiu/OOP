#include <iostream>

class Handler {
protected:
    Handler* next;
public:
    Handler() : next(nullptr) {}
    virtual ~Handler() {}
    void setNext(Handler* next) {
        this->next = next;
    }
    virtual void handle(int request) {
        if (next) {
            next->handle(request);
        }
    }
};

class ConcreteHandler1 : public Handler {
public:
    void handle(int request) override {
        if (request == 1) {
            std::cout << "ConcreteHandler1 handled the request\n";
        } else if (next) {
            next->handle(request);
        }
    }
};

class ConcreteHandler2 : public Handler {
public:
    void handle(int request) override {
        if (request == 2) {
            std::cout << "ConcreteHandler2 handled the request\n";
        } else if (next) {
            next->handle(request);
        }
    }
};

int main() {
    ConcreteHandler1 handler1;
    ConcreteHandler2 handler2;

    handler1.setNext(&handler2);

    handler1.handle(1);
    handler1.handle(2);

    return 0;
}