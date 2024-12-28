#include "conta_palavras.hpp"
#include <utility>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
const std::string testInputFilePath = "input.txt";

void writeContentInInputFile(std::string s) {
  std::ofstream inputFile(testInputFilePath);
  inputFile << s;
  inputFile.close();
}

void clearInputFile() { writeContentInInputFile(""); }

bool vectorsAreEqual(std::vector<std::string> vector1,
                     std::vector<std::string> vector2) {
  if ((int)vector1.size() != (int)vector2.size())
    return false;
  bool flag = true;

  for (int i = 0; i < (int)vector1.size(); i++) {
    flag &= (vector1[i] == vector2[i]);
  }

  return flag;
}

TEST_CASE("Should read input.txt file content", "[readFileContent]") {
  std::string inputContent1 = "Fluminense Futebol Clube";
  writeContentInInputFile(inputContent1);
  REQUIRE(inputContent1 == readFileContent());

  std::string inputContent2 = "Métodos de programação";
  writeContentInInputFile(inputContent2);
  REQUIRE(inputContent2 == readFileContent());

  std::string inputContent3 = "Lucas Gabriel de Oliveira Lima";
  writeContentInInputFile(inputContent3);
  REQUIRE(inputContent3 == readFileContent());

  std::string inputContent4 = "Este texto é o texto que será utilizado";
  writeContentInInputFile(inputContent4);
  REQUIRE(inputContent4 == readFileContent());

  clearInputFile();
}

TEST_CASE("Should read input.txt considering break line and spaces",
          "[readFileContent]") {
  std::string inputContent1 = "Fluminense \nFutebol Clube";
  writeContentInInputFile(inputContent1);
  REQUIRE(inputContent1 == readFileContent());

  std::string inputContent2 = "Cidade\nOcidental";
  writeContentInInputFile(inputContent2);
  REQUIRE(inputContent2 == readFileContent());

  std::string inputContent3 = "Lucas Gabriel de\n Oliveira Lima";
  writeContentInInputFile(inputContent3);
  REQUIRE(inputContent3 == readFileContent());

  std::string inputContent4 =
      "Este\n texto\n é\n o\n texto\n que será\n utilizado";
  writeContentInInputFile(inputContent4);
  REQUIRE(inputContent4 == readFileContent());

  clearInputFile();
}

TEST_CASE("Should split the string words and return a vector with then",
          "[splitStringContentInWords]") {
  std::string str1 =
      "Sou tricolor de coração\n sou do clube tantas vezes campeão";
  std::vector<std::string> expectedReturn1 = {
      "Sou", "tricolor", "de",     "coração", "sou",
      "do",  "clube",    "tantas", "vezes",   "campeão"};
  REQUIRE(vectorsAreEqual(expectedReturn1, splitStringContentInWords(str1)));

  std::string str2 = "O objetivo deste trabalho é utilizar o desenvolvimento "
                     "orientado a testes";
  std::vector<std::string> expectedReturn2 = {
      "O", "objetivo",        "deste",     "trabalho", "é",     "utilizar",
      "o", "desenvolvimento", "orientado", "a",        "testes"};
  REQUIRE(vectorsAreEqual(expectedReturn2, splitStringContentInWords(str2)));

  std::string str3 = "Este texto é o texto que será utilizado";
  std::vector<std::string> expectedReturn3 = {
      "Este", "texto", "é", "o", "texto", "que", "será", "utilizado",
  };
  REQUIRE(vectorsAreEqual(expectedReturn3, splitStringContentInWords(str3)));

  std::string str4 = "Bom bom       dia";
  std::vector<std::string> expectedReturn4 = {"Bom", "bom", "dia"};
  REQUIRE(vectorsAreEqual(expectedReturn4, splitStringContentInWords(str4)));

  std::string str5 = "German    Ezequiel Cano \n  \n Recalde";
  std::vector<std::string> expectedReturn5 = {
      "German",
      "Ezequiel",
      "Cano",
      "Recalde",
  };
  REQUIRE(vectorsAreEqual(expectedReturn5, splitStringContentInWords(str5)));
}

TEST_CASE("Should not contain space or break line in a single word",
          "[splitStringContentInWords]") {
  std::vector<std::string> words;
  auto checkIfNotContainSpaceAndBreakLine = [](std::vector<std::string> &v) {
    bool flag = true;

    for (std::string s : v) {
      flag &= (s.find(' ') == s.npos) && (s.find('\n') && s.npos);
    }
    return flag;
  };

  std::string str1 =
      "Sou tricolor de coração\n sou do clube tantas vezes campeão";
  words = splitStringContentInWords(str1);
  REQUIRE(checkIfNotContainSpaceAndBreakLine(words));

  std::string str2 = "O objetivo deste trabalho é utilizar o desenvolvimento "
                     "orientado a testes";
  words = splitStringContentInWords(str2);
  REQUIRE(checkIfNotContainSpaceAndBreakLine(words));

  std::string str3 = "Este texto é o texto que será utilizado";
  words = splitStringContentInWords(str3);
  REQUIRE(checkIfNotContainSpaceAndBreakLine(words));

  std::string str4 = "Bom bom       dia";
  words = splitStringContentInWords(str4);
  REQUIRE(checkIfNotContainSpaceAndBreakLine(words));

  std::string str5 = "German    Ezequiel Cano \n   \n Recalde";
  words = splitStringContentInWords(str5);
  REQUIRE(checkIfNotContainSpaceAndBreakLine(words));
}

TEST_CASE("Should count the frequency of each word in the input file",
          "[getWordsCount]") {

  auto checkWordsCount = [](const std::vector<std::pair<std::string, int>> &v,
                            WordsCounter &counter) {
    bool flag = true;
    for (std::pair<std::string, int> p : v) {
      flag &= counter.getWordCount(p.first) == p.second;
    }

    flag &= ((int)v.size() == counter.size());

    return flag;
  };

  std::string content1 = "Fluminense Futebol Clube";
  writeContentInInputFile(content1);
  WordsCounter count1 = getWordsCount();
  std::vector<std::pair<std::string, int>> expectedResult1 = {
      {"Fluminense", 1},
      {"Futebol", 1},
      {"Clube", 1},
  };
  REQUIRE(checkWordsCount(expectedResult1, count1));

  std::string content2 = "Este texto é o texto que será utilizado";
  writeContentInInputFile(content2);
  WordsCounter count2 = getWordsCount();
  std::vector<std::pair<std::string, int>> expectedResult2 = {
      {"Este", 1}, {"texto", 2}, {"é", 1},         {"o", 1},
      {"que", 1},  {"será", 1},  {"utilizado", 1},
  };
  REQUIRE(checkWordsCount(expectedResult2, count2));

  std::string content3 = "zero oito zero quatro dois zero zero cinco";
  writeContentInInputFile(content3);
  WordsCounter count3 = getWordsCount();
  std::vector<std::pair<std::string, int>> expectedResult3 = {
      {"zero", 4},
      {"oito", 1},
      {"dois", 1},
      {"quatro", 1},
      {"cinco", 1},
  };
  REQUIRE(checkWordsCount(expectedResult3, count3));

  std::string content4 = "Bom bom bOm boM bom BoM";
  writeContentInInputFile(content4);
  WordsCounter count4 = getWordsCount();
  std::vector<std::pair<std::string, int>> expectedResult4 = {
      {"bom", 2},
      {"Bom", 1},
      {"boM", 1},
      {"bOm", 1},
      {"BoM", 1},
  };
  REQUIRE(checkWordsCount(expectedResult4, count4));

  clearInputFile();
}