#include <iostream>
#include <vector>
#include <string>

// ����� �������� ���������
class Item {
    std::string name;
public:
    Item(const std::string& n = "") : name(n) {}
    std::string GetName() const { return name; }
};

// ��������� � �������� ��� ���������
class Collection {
    std::vector<Item> items;
public:
    Collection(int size) : items(size) {}

    int Count() const { return static_cast<int>(items.size()); }
    Item& operator[](int i) { return items[i]; }
    const Item& GetItem(int i) const { return items[i]; }
};

// �������� � ������������ ������� ����
class Iterator {
    const Collection& collection;
    int current;
    int step;
public:
    Iterator(const Collection& c, int step = 1) : collection(c), current(0), step(step) {}
    void First() { current = 0; }
    void Next() { current += step; }
    bool IsDone() const { return current >= collection.Count(); }
    Item CurrentItem() const {
        if (!IsDone()) return collection.GetItem(current);
        return Item(""); // ���������� ������ ������� ���� ��� ���������
    }
};

int main() {
    setlocale(LC_ALL, "");

    Collection col(10);
    for (int i = 0; i < 10; ++i)
        col[i] = Item("Item " + std::to_string(i));

    Iterator it(col, 2); // ������� ����� 1 (��� 2)
    std::cout << "������� ����� 1 (step = 2):" << std::endl;
    for (it.First(); !it.IsDone(); it.Next())
        std::cout << it.CurrentItem().GetName() << std::endl;

    Iterator it2(col, 1); // ������� �������
    std::cout << "������� ������� (step = 1):" << std::endl;
    for (it2.First(); !it2.IsDone(); it2.Next())
        std::cout << it2.CurrentItem().GetName() << std::endl;

    return 0;
}