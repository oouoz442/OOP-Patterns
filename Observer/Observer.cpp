#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <windows.h>

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

class CorrectorWithFix : public Observer {
private:
    vector<string> dictionary = { "hello", "world", "test", "the", "word" };

    int DamerauLevenshtein(const string& s1, const string& s2) {
        int len1 = s1.size();
        int len2 = s2.size();
        vector<vector<int>> d(len1 + 1, vector<int>(len2 + 1));

        for (int i = 0; i <= len1; ++i) d[i][0] = i;
        for (int j = 0; j <= len2; ++j) d[0][j] = j;

        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

                int del = d[i - 1][j] + 1;         // удаление
                int ins = d[i][j - 1] + 1;         // вставка
                int rep = d[i - 1][j - 1] + cost;  // замена

                d[i][j] = min(min(del, ins), rep);

                if (i > 1 && j > 1 &&
                    s1[i - 1] == s2[j - 2] &&
                    s1[i - 2] == s2[j - 1]) {
                    d[i][j] = min(d[i][j], d[i - 2][j - 2] + cost); // транспозиция
                }
            }
        }

        return d[len1][len2];
    }

public:
    void Update(const string& word) override {
        cout << "[Corrector] Checking word: " << word << endl;

        for (const string& correct : dictionary) {
            int dist = DamerauLevenshtein(word, correct);
            if (dist <= 1 && word != correct) {
                cout << "   Did you mean: '" << correct << "'? (distance = " << dist << ")\n";
                return;
            }
        }

        cout << "  ✓ Word seems correct.\n";
    }
};

// === Пример ===
int main() {
    setlocale(LC_ALL, "");
    SetConsoleOutputCP(CP_UTF8);
    auto writer = make_shared<WordWriter>();

    auto uaTranslator = make_shared<EngToUkrTranslator>();
    auto ruTranslator = make_shared<EngToRusTranslator>();
    auto corrector = make_shared<CorrectorWithFix>();

    writer->Attach(uaTranslator);
    writer->Attach(ruTranslator);
    writer->Attach(corrector);

    writer->TypeWord("hello");
    writer->TypeWord("word");
    writer->TypeWord("teh");

    return 0;
}