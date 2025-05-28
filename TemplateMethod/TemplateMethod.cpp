#include <iostream>

// ����������� ����� (������ ���������)
class AbstractClass {
public:
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;

    // ��������� ����� (�������� ��������)
    void TemplateMethod() {
        PrimitiveOperation1();
        PrimitiveOperation2();
        std::cout << std::endl;
    }
};

// ���������� ���������� A
class ConcreteClassA : public AbstractClass {
public:
    void PrimitiveOperation1() override {
        std::cout << "ConcreteClassA.PrimitiveOperation1()" << std::endl;
    }
    void PrimitiveOperation2() override {
        std::cout << "ConcreteClassA.PrimitiveOperation2()" << std::endl;
    }
};

// ���������� ���������� B
class ConcreteClassB : public AbstractClass {
public:
    void PrimitiveOperation1() override {
        std::cout << "ConcreteClassB.PrimitiveOperation1()" << std::endl;
    }
    void PrimitiveOperation2() override {
        std::cout << "ConcreteClassB.PrimitiveOperation2()" << std::endl;
    }
};

int main() {
    AbstractClass* objA = new ConcreteClassA();
    objA->TemplateMethod();
    delete objA;

    AbstractClass* objB = new ConcreteClassB();
    objB->TemplateMethod();
    delete objB;

    return 0;
}