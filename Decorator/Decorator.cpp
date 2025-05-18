#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// === Абстрактный компонент ===
class WiseCollection {
public:
    virtual double Sum() const = 0;
    virtual double Product() const = 0;
    virtual ~WiseCollection() = default;
};

// === Конкретный компонент ===
class SimpleWiseCollection : public WiseCollection {
private:
    vector<double> data;

public:
    SimpleWiseCollection(const vector<double>& values) : data(values) {}

    double Sum() const override {
        double sum = 0;
        for (double val : data) sum += val;
        return sum;
    }

    double Product() const override {
        double prod = 1;
        for (double val : data) prod *= val;
        return prod;
    }
};

// === Базовый декоратор ===
class WiseDecorator : public WiseCollection {
protected:
    shared_ptr<WiseCollection> collection;

public:
    WiseDecorator(shared_ptr<WiseCollection> coll) : collection(coll) {}

    double Sum() const override {
        return collection->Sum();
    }

    double Product() const override {
        return collection->Product();
    }
};

// === Конкретный декоратор: Ограничитель ===
class BoundedCollection : public WiseDecorator {
private:
    double bound;

public:
    BoundedCollection(shared_ptr<WiseCollection> coll, double b)
        : WiseDecorator(coll), bound(b) {}

    double Sum() const override {
        return min(WiseDecorator::Sum(), bound);
    }

    double Product() const override {
        return min(WiseDecorator::Product(), bound);
    }
};

// === main() ===
int main() {
    vector<double> values = { 1.5, 2.0, 3.0 };
    auto simple = make_shared<SimpleWiseCollection>(values);

    auto bounded = make_shared<BoundedCollection>(simple, 5.0);

    cout << "Bounded Sum: " << bounded->Sum() << endl;
    cout << "Bounded Product: " << bounded->Product() << endl;

    return 0;
}