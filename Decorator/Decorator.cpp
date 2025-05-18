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

// === Декоратор ограничения результата ===
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

// === Декоратор логирования ===
class LoggingDecorator : public WiseDecorator {
public:
    LoggingDecorator(shared_ptr<WiseCollection> coll)
        : WiseDecorator(coll) {}

    double Sum() const override {
        double result = WiseDecorator::Sum();
        cout << "[Log] Sum = " << result << endl;
        return result;
    }

    double Product() const override {
        double result = WiseDecorator::Product();
        cout << "[Log] Product = " << result << endl;
        return result;
    }
};

// === Декоратор фильтрации по порогу ===
class ThresholdFilterDecorator : public WiseDecorator {
private:
    double threshold;

public:
    ThresholdFilterDecorator(shared_ptr<WiseCollection> coll, double t)
        : WiseDecorator(coll), threshold(t) {}

    double Sum() const override {
        double rawSum = collection->Sum();
        cout << "[Filter] Applied threshold = " << threshold << endl;
        return (rawSum >= threshold) ? rawSum : 0.0;
    }

    double Product() const override {
        double rawProd = collection->Product();
        cout << "[Filter] Applied threshold = " << threshold << endl;
        return (rawProd >= threshold) ? rawProd : 1.0;
    }
};

// === main() ===
int main() {
    vector<double> values = { 1.5, 2.0, 3.0 };  // sum = 6.5, product = 9.0
    auto simple = make_shared<SimpleWiseCollection>(values);

    // Цепочка декораторов: фильтрация -> логирование -> ограничение
    auto filtered = make_shared<ThresholdFilterDecorator>(simple, 5.0);
    auto logged = make_shared<LoggingDecorator>(filtered);
    auto bounded = make_shared<BoundedCollection>(logged, 7.0);

    cout << "Final Sum: " << bounded->Sum() << endl;
    cout << "Final Product: " << bounded->Product() << endl;

    return 0;
}