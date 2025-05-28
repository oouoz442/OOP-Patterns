#include <iostream>
#include <cmath>

// ��������� ������������ �������
class AnyFunction {
public:
    virtual double Y(double x) const = 0;
    virtual ~AnyFunction() = default;
};

// ������: ������� ��������� (a * x^2 + b)
class Hyperbola : public AnyFunction {
    double a, b;
public:
    Hyperbola(double a, double b) : a(a), b(b) {}
    double Y(double x) const override {
        return a * x * x + b;
    }
};

// ����������� ����� ��������� (Template Method)
class CommonIntegral {
protected:
    double start, finish;
    int stepNumber;
    const AnyFunction* func;
public:
    CommonIntegral(double start, double finish, int stepNumber, const AnyFunction* func)
        : start(start), finish(finish), stepNumber(stepNumber), func(func) {}

    // ����� ��������� � ����������� �����
    virtual double IntegralPart(double left, double right) const = 0;

    // ��������� ����� ���������� ���������
    double Calculate() const {
        double step = (finish - start) / stepNumber;
        double s = 0.0;
        for (int i = 0; i < stepNumber; ++i)
            s += IntegralPart(start + step * i, start + step * (i + 1));
        return s;
    }

    virtual ~CommonIntegral() = default;
};

// ����� ������ ����� ���������������
class LeftRectangle : public CommonIntegral {
public:
    LeftRectangle(double start, double finish, int stepNumber, const AnyFunction* func)
        : CommonIntegral(start, finish, stepNumber, func) {}

    double IntegralPart(double left, double right) const override {
        return func->Y(left) * (right - left);
    }
};

// --- ��������� ����� �������� ---

class Trapezoid : public CommonIntegral {
public:
    Trapezoid(double start, double finish, int stepNumber, const AnyFunction* func)
        : CommonIntegral(start, finish, stepNumber, func) {}

    double IntegralPart(double left, double right) const override {
        // S = (f(a) + f(b)) / 2 * (b - a)
        return (func->Y(left) + func->Y(right)) * (right - left) / 2.0;
    }
}; 


// --- ������ ������������� ---
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