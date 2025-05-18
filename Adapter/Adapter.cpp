#include <iostream>
#include <memory>
using namespace std;

// === Целевой интерфейс ===
class Target {
public:
    virtual void Request() const = 0;
    virtual ~Target() = default;
};

// === Адаптируемый класс ===
class Adaptee {
public:
    void SpecificRequest() const {
        cout << "Adaptee's specific request\n";
    }
};

// === Адаптер ===
class Adapter : public Target {
private:
    shared_ptr<Adaptee> adaptee;

public:
    Adapter(shared_ptr<Adaptee> a) : adaptee(a) {}

    void Request() const override {
        adaptee->SpecificRequest();
    }
};

// === main ===
int main() {
    shared_ptr<Adaptee> adaptee = make_shared<Adaptee>();
    shared_ptr<Target> target = make_shared<Adapter>(adaptee);

    target->Request();  // Вызывает метод Adaptee
    return 0;
}