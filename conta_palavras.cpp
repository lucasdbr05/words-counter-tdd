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

std::vector<std::string> splitStringContent(std::string str) {
    std::vector<std::string> words;
    return words;
}