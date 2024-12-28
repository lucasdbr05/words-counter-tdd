#include "conta_palavras.hpp"

/**
 * @brief           This function reads the content in the default input file
 * and return it as a string.
 *
 * @return std::string          The content of the input file.
 */
std::string readFileContent() {
  const std::string inputFilePath = "input.txt";
  std::ifstream file(inputFilePath);

  std::string fileFullContent;
  std::string lineContent;
  while (getline(file, lineContent)) {
    fileFullContent += lineContent;
    fileFullContent += '\n';
  }
  fileFullContent.pop_back();

  file.close();

  return fileFullContent;
}

/**
 * @brief this function gets a string and split it in its black spaces
 * (considering space and break line)
 *
 * @param str  string to be splited in its blank spaces
 *
 * @return std::vector<std::string> a vector containing the words present in the
 * "str" string
 */
std::vector<std::string> splitStringContentInWords(std::string str) {
  std::vector<std::string> words;

  int str_size = str.size();

  std::string current_word = "";
  bool isLetter;

  for (int i = 0; i < str_size; i++) {
    isLetter = (str[i] != ' ') && (str[i] != '\n');
    if (!isLetter) {
      if ((int)current_word.size() > 0) {
        words.push_back(current_word);
      }
      current_word = "";
    }

    if (isLetter) {
      current_word.push_back(str[i]);
    }

    if ((i + 1) == str_size && (int)current_word.size() > 0)
      words.push_back(current_word);
  }

  return words;
}

WordsCounter getWordsCount() {
  WordsCounter wordsCount;

  return wordsCount;
}