#ifndef CONTA_PALAVRAS_HPP_
#define CONTA_PALAVRAS_HPP_

#include <math.h>

#include <algorithm>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <string>
#include <vector>

/**
 * @brief struct to get a collection of words (as strings) and build a frequency
 * counter for each different word
 *
 */
struct WordsCounter {
   private:
    std::map<std::wstring, int> counter;

    // Letter sorted in alphabetical order
    std::wstring alphabetStringOrder =
        L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::map<wchar_t, int> characterOrder;
    std::map<wchar_t, wchar_t> filteredChars;

    // Filtered caracteres in lowercase and without accent
    void buildFilteredCharacters() {
        std::vector<std::pair<wchar_t, std::wstring>> variations = 
          {{L'a', L"ãáâàÃÁÂÀ"}, {L'c', L"çÇ"}, {L'e', L"ẽéêèẼÉÊÈ"}, {L'i', L"ĩíîìĨÍÎÌ"}, {L'o', L"õóôòÕÓÔÒ"}, {L'u', L"ũúûùŨÚÛÙ"}};
        for (int i = 0; i < 26; i++) {
            filteredChars[alphabetStringOrder[i]] = alphabetStringOrder[i];
            filteredChars[alphabetStringOrder[i + 26]] = alphabetStringOrder[i];
        }

        for (auto [filtered, variation] : variations) {
            for (auto ch : variation) {
                filteredChars[ch] = filtered;
            }
        }
    }

    // Index each letter in alphabetical order
    void buildCharacterOrder() {
        for (int i = 0; i < static_cast<int>(alphabetStringOrder.size()) / 2;
             i++) {
            characterOrder[alphabetStringOrder[i]] = i;
        }
    }

    // Format each row on listing words counting formatted
    std::wstring formatListRow(std::pair<std::wstring, int> wordCount) {
        auto intToWString = [](int number) {
            std::wstring s = L"";
            while (number > 0) {
                wchar_t digit = L'0' + (number % 10);
                s = digit + s;
                number /= 10;
            }
            return s;
        };

        return wordCount.first + L": " + intToWString(wordCount.second);
    }

    // Comparator used to sort words
    bool comparator(const std::pair<std::wstring, int>& a,
                    const std::pair<std::wstring, int>& b) {
        int a_size = a.first.size();
        int b_size = b.first.size();

        for (int i = 0; i < std::min(a_size, b_size); i++) {
            if (filteredChars[a.first[i]] == filteredChars[b.first[i]])
                continue;

            return characterOrder[filteredChars[a.first[i]]] <
                   characterOrder[filteredChars[b.first[i]]];
        }
        return a_size < b_size;
    }

   public:
    WordsCounter(std::vector<std::wstring> words) {
        buildFilteredCharacters();
        buildCharacterOrder();

        for (std::wstring s : words) {
            addWord(s);
        }
    }

    /**
     * @brief  get the formatted value of the words counting
     *
     * @return std::wstring the formatted string with the counting of each word
     * sorted alphabetically in increasing order
     */
    std::wstring listWords() {
        std::vector<std::pair<std::wstring, int>> countSorted =
            this->getSortedValues();

        std::wstring list = L"";

        for (std::pair<std::wstring, int> cnt : countSorted) {
            list += formatListRow(cnt) + L'\n';
        }

        return list;
    }

    /**
     * @brief Increase by 1 the counting of the word s in the totol count
     *
     * @param s the word to increase the frequency
     */
    void addWord(std::wstring s) { counter[s]++; }

    /**
     * @brief Get the count of a word s
     *
     * @param s the word to get the frequency
     * @return int the frequency of the word s
     */
    int getWordCount(std::wstring s) { return counter[s]; }

    /**
     * @brief method used to get the words counter's size
     *
     * @return int    defined as the number of different words
     */
    int size() { return counter.size(); }

    /**
     * @brief get the words sorted by the alphabetical order and the frequency
     * of each word
     *
     * @return std::vector<std::pair<std::wstring, int>> a vector sorted in
     * alphabetical order countaining in each pair a word and its frequency
     */
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
 * and return it as a wstring.
 *
 * @return std::wstring          The content of the input file.
 */
std::wstring readFileContent();

/**
 * @brief this function gets a wstring and split it in its black spaces
 * (considering space and break line)
 *
 * @param str  wstring to be splited in its blank spaces
 *
 * @return std::vector<std::wstring> a vector containing the words present in
 * the "str" wstring
 */
std::vector<std::wstring> splitStringContentInWords(std::wstring str);

/**
 * @brief This function gets the content of a file splited considering
 * blank spaces and count the frequency of each word in this text; this count
 * use sensitive case, in other words it differs lower case and upper case
 * character and consider them different
 *
 * @return WordsCounter; A struct that stores  a frequency counter for each word
 * in a text
 */
WordsCounter getWordsCount();

/**
 * @brief Get the Words Count Formatted object. This format uses the pattern
 * "word: frequency\n"the words are sorted lexycographically in ascending order
 * as specified in the sort of the WordsCounter
 *
 * @return std::wstring the object containing the words and its frequency sorted
 * lexycographically in ascending order
 */
std::wstring getWordsCountFormatted();

#endif  // CONTA_PALAVRAS_HPP_
