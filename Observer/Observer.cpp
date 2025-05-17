#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
using namespace std;

// === Интерфейс Observer ===
class Observer {
public:
    virtual void Update(const string& word) = 0;
    virtual ~Observer() = default;
};

// === Интерфейс Subject ===
class Subject {
public:
    virtual void Attach(shared_ptr<Observer> observer) = 0;
    virtual void Detach(shared_ptr<Observer> observer) = 0;
    virtual void Notify(const string& word) = 0;
    virtual ~Subject() = default;
};

// === Конкретный Subject: WordWriter ===
class WordWriter : public Subject {
private:
    vector<shared_ptr<Observer>> observers;

public:
    void Attach(shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void Detach(shared_ptr<Observer> observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void Notify(const string& word) override {
        for (auto& obs : observers) {
            obs->Update(word);
        }
    }

    void TypeWord(const string& word) {
        cout << "\nTyping word: " << word << endl;
        Notify(word);
    }
};

// === Переводчики (Observers) ===
class EngToUkrTranslator : public Observer {
public:
    void Update(const string& word) override {
        cout << "[EN→UA] Translation of '" << word << "' → 'Переклад'" << endl;
    }
};

class EngToRusTranslator : public Observer {
public:
    void Update(const string& word) override {
        cout << "[EN→RU] Translation of '" << word << "' → 'Перевод'" << endl;
    }
};

class WordCorrector : public Observer {
public:
    void Update(const string& word) override {
        cout << "[Corrector] Checking word '" << word << "' for errors...\n";
    }
};

// === Пример ===
int main() {
    auto writer = make_shared<WordWriter>();

    auto uaTranslator = make_shared<EngToUkrTranslator>();
    auto ruTranslator = make_shared<EngToRusTranslator>();
    auto corrector = make_shared<WordCorrector>();

    writer->Attach(uaTranslator);
    writer->Attach(ruTranslator);
    writer->Attach(corrector);

    writer->TypeWord("hello");
    writer->TypeWord("word");
    writer->TypeWord("teh");

    return 0;
}