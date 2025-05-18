#include <iostream>
#include <memory>
using namespace std;

// === Абстрактный интерфейс (Component) ===
class Component {
public:
    virtual void Operation() const = 0;
    virtual ~Component() = default;
};

// === Конкретный компонент (ConcreteComponent) ===
class ConcreteComponent : public Component {
public:
    void Operation() const override {
        cout << "ConcreteComponent operation\n";
    }
};

// === Базовый декоратор (Decorator) ===
class Decorator : public Component {
protected:
    shared_ptr<Component> component;

public:
    Decorator(shared_ptr<Component> comp) : component(comp) {}

    void Operation() const override {
        component->Operation();
    }
};

// === Конкретный декоратор A ===
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(shared_ptr<Component> comp) : Decorator(comp) {}

    void Operation() const override {
        Decorator::Operation();
        cout << " + ConcreteDecoratorA enhancement\n";
    }
};

// === Конкретный декоратор B ===
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