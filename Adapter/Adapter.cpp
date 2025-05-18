#include <iostream>
#include <string>
#include <memory>
using namespace std;

// === Целевой интерфейс ===
class Sliceable {
public:
    virtual string Slice(int start, int finish) const = 0;
    virtual ~Sliceable() = default;
};

// === Адаптируемый класс ===
class MyString {
private:
    string innerString;

public:
    MyString(const string& s) : innerString(s) {}

    string Substring(int start, int length) const {
        return innerString.substr(start, length);
    }

    int Length() const {
        return innerString.length();
    }
};

// === Адаптер ===
class StringAdapter : public Sliceable {
private:
    shared_ptr<MyString> adaptee;

public:
    StringAdapter(shared_ptr<MyString> ms) : adaptee(ms) {}

    string Slice(int start, int finish) const override {
        if ((start >= 0) && (finish < adaptee->Length()) && (start <= finish)) {
            return adaptee->Substring(start, finish - start + 1);
        }
        else {
            throw runtime_error("Illegal call of Slice method");
        }
    }
};

// === main ===
int main() {
    string s = "Hello, World!";
    shared_ptr<MyString> ms = make_shared<MyString>(s);
    shared_ptr<Sliceable> adapter = make_shared<StringAdapter>(ms);

    cout << adapter->Slice(2, 8) << endl; // llo, Wo

    return 0;
}