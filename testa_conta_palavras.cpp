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

  clearInputFile();
}
TEST_CASE("Should read input.txt considering break line and spaces", "[readFileContent]") {
  std::string inputContent1 = "Fluminense \nFutebol Clube";
  writeContentInInputFile(inputContent1);
  REQUIRE(inputContent1 == readFileContent());

  std::string inputContent2 = "Cidade\nOcidental";
  writeContentInInputFile(inputContent2);
  REQUIRE(inputContent2 == readFileContent());

  std::string inputContent3 = "Lucas Gabriel de\n Oliveira Lima";
  writeContentInInputFile(inputContent3);
  REQUIRE(inputContent3 == readFileContent());

  clearInputFile();
}
