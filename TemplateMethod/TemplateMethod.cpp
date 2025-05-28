#include <iostream>
#include <cmath>

// Интерфейс произвольной функции
class AnyFunction {
public:
    virtual double Y(double x) const = 0;
    virtual ~AnyFunction() = default;
};

// Пример: функция гипербола (a * x^2 + b)
class Hyperbola : public AnyFunction {
    double a, b;
public:
    Hyperbola(double a, double b) : a(a), b(b) {}
    double Y(double x) const override {
        return a * x * x + b;
    }
};

// Абстрактный класс интеграла (Template Method)
class CommonIntegral {
protected:
    double start, finish;
    int stepNumber;
    const AnyFunction* func;
public:
    CommonIntegral(double start, double finish, int stepNumber, const AnyFunction* func)
        : start(start), finish(finish), stepNumber(stepNumber), func(func) {}

    // Часть интеграла — абстрактный метод
    virtual double IntegralPart(double left, double right) const = 0;

    // Шаблонный метод вычисления интеграла
    double Calculate() const {
        double step = (finish - start) / stepNumber;
        double s = 0.0;
        for (int i = 0; i < stepNumber; ++i)
            s += IntegralPart(start + step * i, start + step * (i + 1));
        return s;
    }

    virtual ~CommonIntegral() = default;
};

// Класс метода левых прямоугольников
class LeftRectangle : public CommonIntegral {
public:
    LeftRectangle(double start, double finish, int stepNumber, const AnyFunction* func)
        : CommonIntegral(start, finish, stepNumber, func) {}

    double IntegralPart(double left, double right) const override {
        return func->Y(left) * (right - left);
    }
};

// --- ДОБАВЛЯЕМ МЕТОД ТРАПЕЦИЙ ---

class Trapezoid : public CommonIntegral {
public:
    Trapezoid(double start, double finish, int stepNumber, const AnyFunction* func)
        : CommonIntegral(start, finish, stepNumber, func) {}

    double IntegralPart(double left, double right) const override {
        // S = (f(a) + f(b)) / 2 * (b - a)
        return (func->Y(left) + func->Y(right)) * (right - left) / 2.0;
    }
}; 


// --- Пример использования ---
int main() {
    Hyperbola f(2.0, 3.0);

    CommonIntegral* integral1 = new LeftRectangle(2.0, 5.0, 100, &f);
    std::cout << "Left Rectangle: " << integral1->Calculate() << std::endl;
    delete integral1;

    CommonIntegral* integral2 = new Trapezoid(2.0, 5.0, 100, &f);
    std::cout << "Trapezoid: " << integral2->Calculate() << std::endl;
    delete integral2;

    return 0;
}
//