#include <iostream>
#include <memory>
using namespace std;

// === Абстрактные продукты ===
class AbstractProductA {
public:
    virtual void Show() const = 0;
    virtual ~AbstractProductA() = default;
};

class AbstractProductB {
public:
    virtual void Display() const = 0;
    virtual ~AbstractProductB() = default;
};

// === Конкретные продукты семейства 1 ===
class ProductA1 : public AbstractProductA {
public:
    void Show() const override {
        cout << "ProductA1\n";
    }
};

class ProductB1 : public AbstractProductB {
public:
    void Display() const override {
        cout << "ProductB1\n";
    }
};

// === Конкретные продукты семейства 2 ===
class ProductA2 : public AbstractProductA {
public:
    void Show() const override {
        cout << "ProductA2\n";
    }
};

class ProductB2 : public AbstractProductB {
public:
    void Display() const override {
        cout << "ProductB2\n";
    }
};

// === Абстрактная фабрика ===
class AbstractFactory {
public:
    virtual shared_ptr<AbstractProductA> CreateProductA() const = 0;
    virtual shared_ptr<AbstractProductB> CreateProductB() const = 0;
    virtual ~AbstractFactory() = default;
};

// === Конкретные фабрики ===
class Factory1 : public AbstractFactory {
public:
    shared_ptr<AbstractProductA> CreateProductA() const override {
        return make_shared<ProductA1>();
    }

    shared_ptr<AbstractProductB> CreateProductB() const override {
        return make_shared<ProductB1>();
    }
};

class Factory2 : public AbstractFactory {
public:
    shared_ptr<AbstractProductA> CreateProductA() const override {
        return make_shared<ProductA2>();
    }

    shared_ptr<AbstractProductB> CreateProductB() const override {
        return make_shared<ProductB2>();
    }
};

// === Клиент ===
class Client {
private:
    shared_ptr<AbstractProductA> a;
    shared_ptr<AbstractProductB> b;

public:
    Client(shared_ptr<AbstractFactory> factory) {
        a = factory->CreateProductA();
        b = factory->CreateProductB();
    }

    void Run() {
        a->Show();
        b->Display();
    }
};

// === main() ===
int main() {
    shared_ptr<AbstractFactory> factory1 = make_shared<Factory1>();
    Client client1(factory1);
    client1.Run();

    shared_ptr<AbstractFactory> factory2 = make_shared<Factory2>();
    Client client2(factory2);
    client2.Run();

    return 0;
}