#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// === Интерфейс Observer ===
class Observer {
public:
    virtual void Update(const string& state) = 0;
    virtual ~Observer() = default;
};

// === Интерфейс Subject ===
class Subject {
public:
    virtual void Attach(shared_ptr<Observer> observer) = 0;
    virtual void Detach(shared_ptr<Observer> observer) = 0;
    virtual void Notify() = 0;
    virtual ~Subject() = default;
};

// === Конкретный Subject ===
class ConcreteSubject : public Subject {
private:
    vector<shared_ptr<Observer>> observers;
    string state;
public:
    void Attach(shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void Detach(shared_ptr<Observer> observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void Notify() override {
        for (auto& obs : observers) {
            obs->Update(state);
        }
    }

    void SetState(const string& s) {
        state = s;
        Notify();
    }

    string GetState() const {
        return state;
    }
};

// === Конкретный Observer ===
class ConcreteObserver : public Observer {
private:
    string name;
    string observerState;
public:
    ConcreteObserver(const string& n) : name(n) {}

    void Update(const string& state) override {
        observerState = state;
        cout << "Observer " << name << " updated to state: " << observerState << endl;
    }
};

// === Пример ===
int main() {
    auto subject = make_shared<ConcreteSubject>();

    auto obs1 = make_shared<ConcreteObserver>("X");
    auto obs2 = make_shared<ConcreteObserver>("Y");
    auto obs3 = make_shared<ConcreteObserver>("Z");

    subject->Attach(obs1);
    subject->Attach(obs2);
    subject->Attach(obs3);

    subject->SetState("ABC");

    return 0;
}