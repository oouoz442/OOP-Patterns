#include <iostream>
#include <string>

// Subject � ���������
class Subject {
public:
    virtual ~Subject() {}
    virtual void Request() = 0;
};

// �������� ������
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

    void Request() override { // ������ const!
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
    proxy.Request(); // ������ �������� ������ � ���������� �����
    proxy.Request(); // ������ ��� ������, ������ ���������� �����
    return 0;
}