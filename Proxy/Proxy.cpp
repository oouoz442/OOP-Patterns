#include <iostream>
#include <vector>
#include <stdexcept>

// Абстрактный интерфейс
class Fibonacci {
public:
    virtual ~Fibonacci() {}
    virtual int GetFibonacci(int n) = 0;
};

// "Пам'ятающий" объект (реальный кэш)
class RetentiveFibonacci : public Fibonacci {
    std::vector<int> fibNumbers;
public:
    RetentiveFibonacci() {
        fibNumbers.push_back(1);
        fibNumbers.push_back(1);
    }
    int MaxIndex() const { return static_cast<int>(fibNumbers.size()); }
    int Last() const { return fibNumbers.back(); }
    int Penultimate() const { return fibNumbers[fibNumbers.size() - 2]; }

    void Add(const std::vector<int>& appendix) {
        fibNumbers.insert(fibNumbers.end(), appendix.begin(), appendix.end());
    }
    int GetFibonacci(int n) override {
        if (n <= MaxIndex())
            return fibNumbers[n - 1];
        throw std::runtime_error("This Fibonacci number was not yet calculated.");
    }
};

// Proxy
class RealFibonacci : public Fibonacci {
    RetentiveFibonacci retentiveFibonacci;
public:
    int GetFibonacci(int n) override {
        if (n > retentiveFibonacci.MaxIndex()) {
            std::vector<int> appendix;
            appendix.push_back(retentiveFibonacci.Penultimate());
            appendix.push_back(retentiveFibonacci.Last());
            for (int i = retentiveFibonacci.MaxIndex(); i < n; ++i)
                appendix.push_back(appendix[appendix.size() - 2] + appendix[appendix.size() - 1]);
            // Удаляем первые два элемента
            appendix.erase(appendix.begin(), appendix.begin() + 2);
            retentiveFibonacci.Add(appendix);
        }
        return retentiveFibonacci.GetFibonacci(n);
    }
};

int main() {
    RealFibonacci proxy;
    std::cout << proxy.GetFibonacci(5) << std::endl;
    std::cout << proxy.GetFibonacci(20) << std::endl;
    std::cout << proxy.GetFibonacci(10) << std::endl;
    return 0;
}