#include <iostream>
#include <vector>
#include <string>

// �����-������� ��� ���� ������� ����
class WordPairsAggregate {
    std::vector<std::string> englishWords;
    std::vector<std::string> ukrainianWords;
public:
    WordPairsAggregate(const std::vector<std::string>& en, const std::vector<std::string>& ua)
        : englishWords(en), ukrainianWords(ua) {}

    int Count() const { return englishWords.size(); }

    const std::string& GetEnglish(int i) const { return englishWords.at(i); }
    const std::string& GetUkrainian(int i) const { return ukrainianWords.at(i); }
};

// �������� �� ���������� ������
class EnglishIterator {
    const WordPairsAggregate& agg;
    int current;
public:
    EnglishIterator(const WordPairsAggregate& a) : agg(a), current(0) {}
    void First() { current = 0; }
    void Next() { ++current; }
    bool IsDone() const { return current >= agg.Count(); }
    std::string CurrentItem() const { return agg.GetEnglish(current); }
};

// �������� �� ���������� ������
class UkrainianIterator {
    const WordPairsAggregate& agg;
    int current;
public:
    UkrainianIterator(const WordPairsAggregate& a) : agg(a), current(0) {}
    void First() { current = 0; }
    void Next() { ++current; }
    bool IsDone() const { return current >= agg.Count(); }
    std::string CurrentItem() const { return agg.GetUkrainian(current); }
};

// �������� �� ����� ����
class PairIterator {
    const WordPairsAggregate& agg;
    int current;
public:
    PairIterator(const WordPairsAggregate& a) : agg(a), current(0) {}
    void First() { current = 0; }
    void Next() { ++current; }
    bool IsDone() const { return current >= agg.Count(); }
    std::pair<std::string, std::string> CurrentItem() const {
        return { agg.GetEnglish(current), agg.GetUkrainian(current) };
    }
};

int main() {
    setlocale(LC_ALL, "");

    std::vector<std::string> en = { "cat", "dog", "apple", "book" };
    std::vector<std::string> ua = { "��", "���", "������", "�����" };
    WordPairsAggregate dict(en, ua);

    // ���������� �����
    std::cout << "������ ���������� ����:\n";
    EnglishIterator it_en(dict);
    for (it_en.First(); !it_en.IsDone(); it_en.Next())
        std::cout << it_en.CurrentItem() << std::endl;

    // ���������� �����
    std::cout << "\n������ ���������� ����:\n";
    UkrainianIterator it_ua(dict);
    for (it_ua.First(); !it_ua.IsDone(); it_ua.Next())
        std::cout << it_ua.CurrentItem() << std::endl;

    // ���� ����
    std::cout << "\n������ ��� <����������-���������� �����>:\n";
    PairIterator it_pair(dict);
    for (it_pair.First(); !it_pair.IsDone(); it_pair.Next()) {
        auto pair = it_pair.CurrentItem();
        std::cout << "<" << pair.first << " - " << pair.second << ">" << std::endl;
    }

    return 0;
}