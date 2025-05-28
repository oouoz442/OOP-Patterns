#include <iostream>
#include <vector>

// Абстрактный класс
class DataAccessObject {
public:
    // Шаблонный метод
    void Run() {
        Connect();
        Select();
        Process();
        Disconnect();
    }
    virtual void Connect() = 0;
    virtual void Select() = 0;
    virtual void Process() = 0;
    virtual void Disconnect() = 0;
};

// Конкретная реализация для категорий
class Categories : public DataAccessObject {
public:
    void Connect() override {
        std::cout << "Categories: Connecting to database..." << std::endl;
    }
    void Select() override {
        std::cout << "Categories: Selecting data..." << std::endl;
        data = { "Cat1", "Cat2", "Cat3" };
    }
    void Process() override {
        std::cout << "Categories: Processing data:" << std::endl;
        for (const auto& d : data)
            std::cout << "  " << d << std::endl;
    }
    void Disconnect() override {
        std::cout << "Categories: Disconnecting from database." << std::endl;
    }
private:
    std::vector<std::string> data;
};

// Конкретная реализация для товаров
class Products : public DataAccessObject {
public:
    void Connect() override {
        std::cout << "Products: Connecting to database..." << std::endl;
    }
    void Select() override {
        std::cout << "Products: Selecting data..." << std::endl;
        data = { "Prod1", "Prod2" };
    }
    void Process() override {
        std::cout << "Products: Processing data:" << std::endl;
        for (const auto& d : data)
            std::cout << "  " << d << std::endl;
    }
    void Disconnect() override {
        std::cout << "Products: Disconnecting from database." << std::endl;
    }
private:
    std::vector<std::string> data;
};

int main() {
    DataAccessObject* dao = new Categories();
    dao->Run();
    delete dao;

    dao = new Products();
    dao->Run();
    delete dao;

    return 0;
}