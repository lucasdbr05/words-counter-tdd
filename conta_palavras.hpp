#ifndef CONTA_PALAVRAS_HPP_
#define CONTA_PALAVRAS_HPP_

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/**
 * @brief struct to get a collection of words (as strings) and build a frequency
 * counter for each different word
 *
 */
struct WordsCounter {
    std::map<std::string, int> counter;

    WordsCounter() {}

    WordsCounter(std::vector<std::string> words) {
        for (std::string s : words) {
            addWord(s);
        }
    }

    void addWord(std::string s) { counter[s]++; }
    int getWordCount(std::string s) { return counter[s]; }
    int size() { return counter.size(); }
};

/**
 * @brief           This function reads the content in the default input file
 * and return it as a string.
 *
 * @return std::string          The content of the input file.
 */
std::string readFileContent();

/**
 * @brief this function gets a string and split it in its black spaces
 * (considering space and break line)
 *
 * @param str  string to be splited in its blank spaces
 *
 * @return std::vector<std::string> a vector containing the words present in the
 * "str" string
 */
std::vector<std::string> splitStringContentInWords(std::string str);

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
