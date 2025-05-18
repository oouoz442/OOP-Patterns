#include <iostream>
#include <memory>
using namespace std;

// === Продукт ===
class Product {
public:
    virtual void Use() const = 0;
    virtual ~Product() = default;
};

// === Конкретные продукты ===
class ConcreteProductA : public Product {
public:
    void Use() const override {
        cout << "Using Product A" << endl;
    }
};

class ConcreteProductB : public Product {
public:
    void Use() const override {
        cout << "Using Product B" << endl;
    }
};

// === Создатель ===
class Creator {
public:
    virtual shared_ptr<Product> FactoryMethod() const = 0;

    void SomeOperation() const {
        auto product = FactoryMethod();
        product->Use();
    }

    virtual ~Creator() = default;
};

// === Конкретные создатели ===
class CreatorA : public Creator {
public:
    shared_ptr<Product> FactoryMethod() const override {
        return make_shared<ConcreteProductA>();
    }
};

class CreatorB : public Creator {
public:
    shared_ptr<Product> FactoryMethod() const override {
        return make_shared<ConcreteProductB>();
    }
};

// === main() ===
int main() {
    shared_ptr<Creator> creatorA = make_shared<CreatorA>();
    creatorA->SomeOperation();

    shared_ptr<Creator> creatorB = make_shared<CreatorB>();
    creatorB->SomeOperation();

    return 0;
}