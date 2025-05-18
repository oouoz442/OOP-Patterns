#include <iostream>
#include <memory>
using namespace std;

// === ����������� ��������� (Component) ===
class Component {
public:
    virtual void Operation() const = 0;
    virtual ~Component() = default;
};

// === ���������� ��������� (ConcreteComponent) ===
class ConcreteComponent : public Component {
public:
    void Operation() const override {
        cout << "ConcreteComponent operation\n";
    }
};

// === ������� ��������� (Decorator) ===
class Decorator : public Component {
protected:
    shared_ptr<Component> component;

public:
    Decorator(shared_ptr<Component> comp) : component(comp) {}

    void Operation() const override {
        component->Operation();
    }
};

// === ���������� ��������� A ===
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(shared_ptr<Component> comp) : Decorator(comp) {}

    void Operation() const override {
        Decorator::Operation();
        cout << " + ConcreteDecoratorA enhancement\n";
    }
};

// === ���������� ��������� B ===
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(shared_ptr<Component> comp) : Decorator(comp) {}

    void Operation() const override {
        Decorator::Operation();
        cout << " + ConcreteDecoratorB enhancement\n";
    }
};

// === main() ===
int main() {
    shared_ptr<Component> simple = make_shared<ConcreteComponent>();
    shared_ptr<Component> decorated = make_shared<ConcreteDecoratorB>(
        make_shared<ConcreteDecoratorA>(simple));

    decorated->Operation();

    return 0;
}