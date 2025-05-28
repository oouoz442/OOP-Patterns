#include <iostream>
#include <vector>
#include <stdexcept>
#include <chrono>

// Абстрактный интерфейс
class Fibonacci {
public:
    virtual ~Fibonacci() {}
    virtual int GetFibonacci(int n) = 0;
};

// Класс-реализация с кэшем
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

// Proxy (реальный объект с расширением)
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
            // Удаляем первые два вспомогательных элемента
            appendix.erase(appendix.begin(), appendix.begin() + 2);
            retentiveFibonacci.Add(appendix);
        }
        return retentiveFibonacci.GetFibonacci(n);
    }
};

int main() {
    RealFibonacci proxy;
    // Тест: несколько чисел, среди них есть повторное вычисление (уже закэшировано)
    int testValues[] = { 5, 20, 10, 20 };
    for (int n : testValues) {
        auto start = std::chrono::high_resolution_clock::now();
        int result = proxy.GetFibonacci(n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed = end - start;
        std::cout << "Fibonacci(" << n << ") = " << result
            << " | Time: " << elapsed.count() << " microseconds" << std::endl;
    }
    return 0;
}