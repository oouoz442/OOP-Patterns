#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

// Forward declaration WordElement
class WordElement;

// Абстрактный компонент
class TextElement {
protected:
    TextElement* parent = nullptr;
public:
    virtual ~TextElement() {}
    void SetParent(TextElement* p) { parent = p; }
    virtual void Add(TextElement* element) {}
    virtual void Remove(TextElement* element) {}
    virtual void Display() const = 0;
};

// "Целый текст" (корень)
class WholeText : public TextElement {
    std::string title;
    std::vector<TextElement*> chapters;
public:
    WholeText(const std::string& t) : title(t) {}

    void Add(TextElement* element) override {
        chapters.push_back(element);
        element->SetParent(this);
    }
    void Remove(TextElement* element) override {
        auto it = std::remove(chapters.begin(), chapters.end(), element);
        if (it != chapters.end()) chapters.erase(it, chapters.end());
    }
    void Display() const override {
        for (char ch : title)
            std::cout << (char)std::toupper(ch) << ' ';
        std::cout << "\n\n";
        for (auto chapter : chapters) chapter->Display();
    }
};

// Глава
class ChapterElement : public TextElement {
    std::string title;
    std::vector<TextElement*> paragraphs;
public:
    ChapterElement(const std::string& t) : title(t) {}
    void Add(TextElement* element) override {
        paragraphs.push_back(element);
        element->SetParent(this);
    }
    void Remove(TextElement* element) override {
        auto it = std::remove(paragraphs.begin(), paragraphs.end(), element);
        if (it != paragraphs.end()) paragraphs.erase(it, paragraphs.end());
    }
    void Display() const override {
        std::cout << title << std::endl << std::endl;
        for (auto par : paragraphs) par->Display();
    }
};

// Объявляем ParagraphElement заранее, метод Display реализуем позже
class ParagraphElement : public TextElement {
    std::vector<TextElement*> words;
    int width;
public:
    ParagraphElement(int w) : width(w) {}
    void Add(TextElement* element) override {
        words.push_back(element);
        element->SetParent(this);
    }
    void Remove(TextElement* element) override {
        auto it = std::remove(words.begin(), words.end(), element);
        if (it != words.end()) words.erase(it, words.end());
    }
    void Display() const override; // только объявление!
};

// Слово (лист)
class WordElement : public TextElement {
    std::string word;
public:
    WordElement(const std::string& w) : word(w) {}
    int GetLength() const { return static_cast<int>(word.length()); }
    void Add(TextElement*) override {
        throw std::runtime_error("Cannot add to a WordElement");
    }
    void Remove(TextElement*) override {
        throw std::runtime_error("Cannot remove from a WordElement");
    }
    void Display(bool capitalize = false) const {
        if (capitalize && !word.empty()) {
            std::string copy = word;
            copy[0] = std::toupper(copy[0]);
            std::cout << copy << " ";
        }
        else {
            std::cout << word << " ";
        }
    }
    void Display() const override { Display(false); }
};

// Теперь определяем метод ParagraphElement::Display
void ParagraphElement::Display() const {
    int horPosition = 0;
    bool first = true;
    for (const auto& word : words) {
        const WordElement* we = dynamic_cast<const WordElement*>(word);
        int len = we ? we->GetLength() : 0;
        if (horPosition + len > width && !first) {
            std::cout << "\n";
            horPosition = 0;
        }
        if (we) we->Display(first);
        else word->Display();
        horPosition += len + 1;
        first = false;
    }
    std::cout << "\n\n";
}

int main() {
    WholeText* book = new WholeText("My great book");
    ChapterElement* chapter1 = new ChapterElement("Introduction");
    ChapterElement* chapter2 = new ChapterElement("Conclusion");
    ParagraphElement* p1 = new ParagraphElement(15);
    ParagraphElement* p2 = new ParagraphElement(25);
    ParagraphElement* p3 = new ParagraphElement(25);
    WordElement* w1 = new WordElement("sunday");
    WordElement* w2 = new WordElement("monday");
    WordElement* w3 = new WordElement("tuesday");
    WordElement* w4 = new WordElement("wednesday");
    WordElement* w5 = new WordElement("thursday");
    WordElement* w6 = new WordElement("friday");
    WordElement* w7 = new WordElement("saturday");

    book->Add(chapter1);
    book->Add(chapter2);
    chapter1->Add(p1);
    chapter1->Add(p2);
    chapter2->Add(p3);
    chapter2->Add(p1);

    p1->Add(w1); p1->Add(w2); p1->Add(w3);
    p2->Add(w4); p2->Add(w5); p2->Add(w6);
    p3->Add(w7); p3->Add(w1); p3->Add(w2);

    book->Display();

    // Очистка памяти
    delete w1; delete w2; delete w3; delete w4; delete w5; delete w6; delete w7;
    delete p1; delete p2; delete p3;
    delete chapter1; delete chapter2; delete book;

    return 0;
}