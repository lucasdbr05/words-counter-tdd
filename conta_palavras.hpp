#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct WordsCounter {
  std::map<std::string, int> counter;

  WordsCounter(){};

  WordsCounter(std::vector<std::string> words) {
    for (std::string s : words) {
      addWord(s);
    }
  };

  void addWord(std::string s) { counter[s]++; }
  int getWordCount(std::string s) { return counter[s]; }
  int size() { return counter.size(); }
};

std::string readFileContent();
std::vector<std::string> splitStringContentInWords(std::string str);
WordsCounter getWordsCount();