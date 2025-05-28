#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Component {
protected:
    std::string name;
public:
    Component(const std::string& name) : name(name) {}
    virtual ~Component() = default;
    virtual void Add(Component* component) {}
    virtual void Remove(Component* component) {}
    virtual void Display(int depth) const = 0;
};

class Leaf : public Component {
public:
    Leaf(const std::string& name) : Component(name) {}
    void Display(int depth) const override {
        for (int i = 0; i < depth; ++i) std::cout << "-";
        std::cout << name << std::endl;
    }
};

class Composite : public Component {
    std::vector<Component*> children;
public:
    Composite(const std::string& name) : Component(name) {}
    void Add(Component* component) override {
        children.push_back(component);
    }
    void Remove(Component* component) override {
        auto it = std::remove(children.begin(), children.end(), component);
        if (it != children.end())
            children.erase(it, children.end());
    }
    void Display(int depth) const override {
        for (int i = 0; i < depth; ++i) std::cout << "-";
        std::cout << name << std::endl;
        for (const auto& child : children)
            child->Display(depth + 2);
    }
};

int main() {
    setlocale(LC_ALL, "");

    // �������� ����������� ���������
    Composite* root = new Composite("������");
    root->Add(new Leaf("���� A"));
    root->Add(new Leaf("���� B"));

    Composite* comp = new Composite("�������� X");
    comp->Add(new Leaf("���� XA"));
    comp->Add(new Leaf("���� XB"));

    root->Add(comp);

    Leaf* leafC = new Leaf("���� C");
    root->Add(leafC);

    std::cout << "������ 1:\n";
    root->Display(1);

    // �������� � ������� ����
    Leaf* leafD = new Leaf("���� D");
    root->Add(leafD);
    root->Remove(leafC);

    std::cout << "\n������ 2 (����� ���������� ���� D � �������� ���� C):\n";
    root->Display(1);

    // ������� ������ (��� production � ����������� �����������)
    delete leafC; delete leafD; delete root; delete comp;

    return 0;
}