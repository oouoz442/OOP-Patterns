#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Интерфейс стратегии
class SortStrategy {
public:
    virtual void Sort(vector<int>& data) = 0;
    virtual ~SortStrategy() = default;
};

// Реализация: пузырьковая сортировка
class BubbleSort : public SortStrategy {
public:
    void Sort(vector<int>& data) override {
        cout << "Sorting using Bubble Sort...\n";
        for (size_t i = 0; i < data.size(); ++i)
            for (size_t j = 0; j < data.size() - i - 1; ++j)
                if (data[j] > data[j + 1])
                    swap(data[j], data[j + 1]);
    }
};

// Реализация: сортировка вставками
class InsertionSort : public SortStrategy {
public:
    void Sort(vector<int>& data) override {
        cout << "Sorting using Insertion Sort...\n";
        for (size_t i = 1; i < data.size(); ++i) {
            int key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                --j;
            }
            data[j + 1] = key;
        }
    }
};

// Реализация: быстрая сортировка
class QuickSort : public SortStrategy {
public:
    void Sort(vector<int>& data) override {
        cout << "Sorting using Quick Sort...\n";
        quickSort(data, 0, data.size() - 1);
    }

private:
    void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

// Контекст
class Sorter {
private:
    unique_ptr<SortStrategy> strategy;
public:
    Sorter(SortStrategy* strategy) : strategy(strategy) {}

    void SetStrategy(SortStrategy* newStrategy) {
        strategy.reset(newStrategy);
    }

    void SortData(vector<int>& data) {
        strategy->Sort(data);
    }
};

void Print(const vector<int>& data) {
    for (int n : data) cout << n << " ";
    cout << endl;
}

int main() {
    vector<int> data = { 5, 2, 9, 1, 5, 6 };

    Sorter sorter(new BubbleSort());
    sorter.SortData(data);
    Print(data);

    data = { 5, 2, 9, 1, 5, 6 };
    sorter.SetStrategy(new InsertionSort());
    sorter.SortData(data);
    Print(data);

    data = { 5, 2, 9, 1, 5, 6 };
    sorter.SetStrategy(new QuickSort());
    sorter.SortData(data);
    Print(data);

    return 0;
}