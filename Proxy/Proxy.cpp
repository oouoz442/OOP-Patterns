#include <iostream>
#include <string>

// Subject Ч интерфейс
class Subject {
public:
    virtual ~Subject() {}
    virtual void Request() = 0;
};

// –еальный объект
class RealSubject : public Subject {
public:
    void Request() override {
        std::cout << "RealSubject: Handling request.\n";
    }
};

// Proxy
class Proxy : public Subject {
    RealSubject* realSubject;
public:
    Proxy() : realSubject(nullptr) {}
    ~Proxy() { delete realSubject; }

    void Request() override { // убрали const!
        if (!realSubject) {
            std::cout << "Proxy: Creating RealSubject...\n";
            realSubject = new RealSubject();
        }
        std::cout << "Proxy: Delegating request to RealSubject.\n";
        realSubject->Request();
    }
};

int main() {
    Proxy proxy;
    proxy.Request(); // создаЄт реальный объект и делегирует вызов
    proxy.Request(); // объект уже создан, только делегирует вызов
    return 0;
}