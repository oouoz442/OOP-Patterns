#include <iostream>
#include <memory>
using namespace std;

// === Абстрактные продукты ===
class Herbivore {
public:
    virtual void EatGrass() const = 0;
    virtual ~Herbivore() = default;
};

class Carnivore {
public:
    virtual void Eat(const Herbivore& herbivore) const = 0;
    virtual ~Carnivore() = default;
};

// === Конкретные травоядные ===
class Wildebeest : public Herbivore {
public:
    void EatGrass() const override {
        cout << "Wildebeest grazes.\n";
    }
};

class Bison : public Herbivore {
public:
    void EatGrass() const override {
        cout << "Bison grazes.\n";
    }
};

// === Конкретные хищники ===
class Lion : public Carnivore {
public:
    void Eat(const Herbivore& herbivore) const override {
        cout << "Lion eats Wildebeest.\n";
    }
};

class Wolf : public Carnivore {
public:
    void Eat(const Herbivore& herbivore) const override {
        cout << "Wolf eats Bison.\n";
    }
};

// === Абстрактная фабрика континента ===
class ContinentFactory {
public:
    virtual shared_ptr<Herbivore> CreateHerbivore() const = 0;
    virtual shared_ptr<Carnivore> CreateCarnivore() const = 0;
    virtual ~ContinentFactory() = default;
};

// === Конкретные фабрики континентов ===
class AfricaFactory : public ContinentFactory {
public:
    shared_ptr<Herbivore> CreateHerbivore() const override {
        return make_shared<Wildebeest>();
    }

    shared_ptr<Carnivore> CreateCarnivore() const override {
        return make_shared<Lion>();
    }
};

class AmericaFactory : public ContinentFactory {
public:
    shared_ptr<Herbivore> CreateHerbivore() const override {
        return make_shared<Bison>();
    }

    shared_ptr<Carnivore> CreateCarnivore() const override {
        return make_shared<Wolf>();
    }
};

// === Мир животных ===
class AnimalWorld {
private:
    shared_ptr<Herbivore> herbivore;
    shared_ptr<Carnivore> carnivore;

public:
    AnimalWorld(shared_ptr<ContinentFactory> factory) {
        herbivore = factory->CreateHerbivore();
        carnivore = factory->CreateCarnivore();
    }

    void RunFoodChain() const {
        herbivore->EatGrass();
        carnivore->Eat(*herbivore);
    }
};

// === main() ===
int main() {
    shared_ptr<ContinentFactory> africa = make_shared<AfricaFactory>();
    AnimalWorld world1(africa);
    world1.RunFoodChain();

    shared_ptr<ContinentFactory> america = make_shared<AmericaFactory>();
    AnimalWorld world2(america);
    world2.RunFoodChain();

    return 0;
}