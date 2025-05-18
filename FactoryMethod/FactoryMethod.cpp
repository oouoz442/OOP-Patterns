#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// === Продукт ===
class Document {
public:
    virtual void Open() const = 0;
    virtual ~Document() = default;
};

// === Конкретные документы ===
class MyDoc : public Document {
public:
    void Open() const override {
        cout << "MyDoc opened\n";
    }
};

class ReportDoc : public Document {
public:
    void Open() const override {
        cout << "ReportDoc opened\n";
    }
};

// === Создатель ===
class Application {
protected:
    vector<shared_ptr<Document>> docs;

public:
    void NewDocument() {
        auto doc = CreateDocument();
        docs.push_back(doc);
        doc->Open();
    }

    virtual shared_ptr<Document> CreateDocument() const = 0;

    virtual ~Application() = default;
};

// === Конкретные приложения ===
class MyApp : public Application {
public:
    shared_ptr<Document> CreateDocument() const override {
        return make_shared<MyDoc>();
    }
};

class ReportApp : public Application {
public:
    shared_ptr<Document> CreateDocument() const override {
        return make_shared<ReportDoc>();
    }
};

// === main() ===
int main() {
    shared_ptr<Application> app1 = make_shared<MyApp>();
    app1->NewDocument();  // MyDoc opened

    shared_ptr<Application> app2 = make_shared<ReportApp>();
    app2->NewDocument();  // ReportDoc opened

    return 0;
}