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

TEST_CASE("Should read input.txt file content", "[readFileContent]") {
  std::string inputContent = "Fluminense Futebol Clube";
  writeContentInInputFile(inputContent);
  REQUIRE(inputContent == readFileContent());
}