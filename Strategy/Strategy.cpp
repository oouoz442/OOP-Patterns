#include <iostream>
#include <memory>
using namespace std;

// Стратегия
class Strategy {
public:
    virtual void AlgorithmInterface() = 0;
    virtual ~Strategy() = default;
};

class ConcreteStrategyA : public Strategy {
public:
    void AlgorithmInterface() override {
        cout << "Called ConcreteStrategyA.AlgorithmInterface()\n";
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void AlgorithmInterface() override {
        cout << "Called ConcreteStrategyB.AlgorithmInterface()\n";
    }
};

class ConcreteStrategyC : public Strategy {
public:
    void AlgorithmInterface() override {
        cout << "Called ConcreteStrategyC.AlgorithmInterface()\n";
    }
};

// Контекст
class Context {
private:
    unique_ptr<Strategy> strategy;
public:
    Context(Strategy* strategy) : strategy(strategy) {}
    void ContextInterface() {
        strategy->AlgorithmInterface();
    }
};

int main() {
    Context contextA(new ConcreteStrategyA());
    contextA.ContextInterface();

    Context contextB(new ConcreteStrategyB());
    contextB.ContextInterface();

    Context contextC(new ConcreteStrategyC());
    contextC.ContextInterface();

    return 0;
}