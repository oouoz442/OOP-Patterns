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
        if ((start >= 0) && (finish < adaptee->Length())) {
            if (start <= finish) {
                return adaptee->Substring(start, finish - start + 1);
            }
            else {
                // Перевернутая подстрока
                string reversed;
                for (int i = start; i >= finish; --i) {
                    reversed += adaptee->Substring(i, 1);
                }
                return reversed;
            }
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

    cout << "Normal:   " << adapter->Slice(2, 8) << endl;   // llo, Wo
    cout << "Reversed: " << adapter->Slice(8, 2) << endl;   // oW ,oll

    return 0;
}