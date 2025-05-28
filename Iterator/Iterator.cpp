#include <iostream>
#include <vector>
#include <string>

// ����������� ��������
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual std::string CurrentItem() const = 0;
};

// ����������� ��������� (�������)
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual Iterator* CreateIterator() = 0;
    virtual int Count() const = 0;
    virtual std::string& operator[](int index) = 0;
    virtual const std::string& GetItem(int index) const = 0; // �������� ������!
};

// ���������� ���������
class ConcreteAggregate : public Aggregate {
    std::vector<std::string> items;
public:
    ConcreteAggregate(int size) : items(size) {}

    Iterator* CreateIterator() override;

    int Count() const override { return static_cast<int>(items.size()); }

    std::string& operator[](int index) override { return items[index]; }

    const std::string& GetItem(int index) const override { return items[index]; }
};

// ���������� ��������
class ConcreteIterator : public Iterator {
    const ConcreteAggregate& aggregate;
    int current;
public:
    ConcreteIterator(const ConcreteAggregate& agg) : aggregate(agg), current(0) {}

    void First() override { current = 0; }
    void Next() override { ++current; }
    bool IsDone() const override { return current >= aggregate.Count(); }
    std::string CurrentItem() const override {
        if (!IsDone()) return aggregate.GetItem(current);
        return "";
    }
};

Iterator* ConcreteAggregate::CreateIterator() {
    return new ConcreteIterator(*this);
}

// ������������
int main() {
    setlocale(LC_ALL, "");
    ConcreteAggregate a(4);
    a[0] = "������� A";
    a[1] = "������� B";
    a[2] = "������� C";
    a[3] = "������� D";

    Iterator* it = a.CreateIterator();
    std::cout << "������� ���������:" << std::endl;
    for (it->First(); !it->IsDone(); it->Next()) {
        std::cout << it->CurrentItem() << std::endl;
    }
    delete it;
    return 0;
}