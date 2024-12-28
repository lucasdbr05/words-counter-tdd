#include "conta_palavras.hpp"
#include <fstream>
#include <iostream>
#include <string>

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

  for (int i = 0; i < 5; i++) {
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
}