#ifndef CONTA_PALAVRAS_HPP_
#define CONTA_PALAVRAS_HPP_

#include <math.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

/**
 * @brief struct to get a collection of words (as strings) and build a frequency
 * counter for each different word
 *
 */
struct WordsCounter {
   private:
    std::map<std::wstring, int> counter;
    std::wstring alphabetStringOrder =
        L"aãáâbcçdeẽéêfghiĩíîjklmnñoõóôpqrstuũúûvwxyzAÃÁÂBCÇDEẼÉÊFGHIĨÍÎJKLMNÑOÕ"
        "ÓÔPQRSTUŨÚÛVWXYZ";
    std::map<wchar_t, int> characterOrder;

    void buildCharacterOrder() {
        for (int i = 0; i < static_cast<int>(alphabetStringOrder.size()); i++) {
            characterOrder[alphabetStringOrder[i]] = i;
        }
    }

    bool comparator(const std::pair<std::wstring, int>& a,
                    const std::pair<std::wstring, int>& b) {
        int a_size = a.first.size();
        int b_size = b.first.size();

        for (int i = 0; i < std::min(a_size, b_size); i++) {
            if (a.first[i] == b.first[i])
                continue;

            return characterOrder[a.first[i]] < characterOrder[b.first[i]];
        }
        return a_size < b_size;
    }

   public:
    WordsCounter(std::vector<std::wstring> words) {
        buildCharacterOrder();
        for (std::wstring s : words) {
            addWord(s);
        }
    }

    void addWord(std::wstring s) { counter[s]++; }

    int getWordCount(std::wstring s) { return counter[s]; }

    int size() { return counter.size(); }

    std::vector<std::pair<std::wstring, int>> getSortedValues() {
        std::vector<std::pair<std::wstring, int>> data;
        for (std::pair<std::wstring, int> cnt : counter) {
            data.push_back(cnt);
        }

        std::sort(data.begin(), data.end(),
                  [this](const std::pair<std::wstring, int>& a,
                         const std::pair<std::wstring, int>& b) {
                      return this->comparator(a, b);
                  });

        return data;
    }
};

/**
 * @brief           This function reads the content in the default input file
 * and return it as a string.
 *
 * @return std::wstring          The content of the input file.
 */
std::wstring readFileContent();

/**
 * @brief this function gets a string and split it in its black spaces
 * (considering space and break line)
 *
 * @param str  string to be splited in its blank spaces
 *
 * @return std::vector<std::wstring> a vector containing the words present in the
 * "str" string
 */
std::vector<std::wstring> splitStringContentInWords(std::wstring str);

/**
 * @brief This function reads gets the content of a file splited considering
 * blank spaces and count the frequency of each word in this text; this count
 * use sensitive case, in other words it differs lower case and upper case
 * character and consider them different
 *
 * @return WordsCounter; An struct the keeps a frequency counter for each word
 * in a text
 */
WordsCounter getWordsCount();

#endif  // CONTA_PALAVRAS_HPP_
