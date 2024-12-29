#include <utility>

#include "./conta_palavras.hpp"

#define CATCH_CONFIG_MAIN
#include "./catch.hpp"
const char testInputFilePath[] = "input.txt";

void writeContentInInputFile(std::string s) {
    std::ofstream inputFile(testInputFilePath);
    inputFile << s;
    inputFile.close();
}

std::wstring toWString(std::string s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(s);
}
void clearInputFile() { writeContentInInputFile(""); }

TEST_CASE("Should read input.txt file content", "[readFileContent]") {
    std::string inputContent1 = "Fluminense Futebol Clube";
    writeContentInInputFile(inputContent1);
    REQUIRE(toWString(inputContent1) == readFileContent());

    std::string inputContent2 = "Métodos de programação";
    writeContentInInputFile(inputContent2);
    REQUIRE(toWString(inputContent2) == readFileContent());

    std::string inputContent3 = "Lucas Gabriel de Oliveira Lima";
    writeContentInInputFile(inputContent3);
    REQUIRE(toWString(inputContent3) == readFileContent());

    std::string inputContent4 = "Este texto é o texto que será utilizado";
    writeContentInInputFile(inputContent4);
    REQUIRE(toWString(inputContent4) == readFileContent());

    clearInputFile();
}

TEST_CASE("Should read input.txt considering break line and spaces",
          "[readFileContent]") {
    std::string inputContent1 = "Fluminense \nFutebol Clube";
    writeContentInInputFile(inputContent1);
    REQUIRE(toWString(inputContent1) == readFileContent());

    std::string inputContent2 = "Cidade\nOcidental";
    writeContentInInputFile(inputContent2);
    REQUIRE(toWString(inputContent2) == readFileContent());

    std::string inputContent3 = "Lucas Gabriel de\n Oliveira Lima";
    writeContentInInputFile(inputContent3);
    REQUIRE(toWString(inputContent3) == readFileContent());

    std::string inputContent4 =
        "Este\n texto\n é\n o\n texto\n que será\n utilizado";
    writeContentInInputFile(inputContent4);
    REQUIRE(toWString(inputContent4) == readFileContent());

    clearInputFile();
}

TEST_CASE("Should split the wstring words and return a vector with then",
          "[splitStringContentInWords]") {
    auto vectorsAreEqual = [](std::vector<std::wstring> vector1,
                              std::vector<std::wstring> vector2) {
        if (static_cast<int>(vector1.size()) !=
            static_cast<int>(vector2.size()))
            return false;

        bool flag = true;

        for (int i = 0; i < static_cast<int>(vector1.size()); i++) {
            flag &= (vector1[i] == vector2[i]);
        }

        return flag;
    };

    std::wstring str1 =
        L"Sou tricolor de coração\n sou do clube tantas vezes campeão";
    std::vector<std::wstring> expectedReturn1 = {
        L"Sou", L"tricolor", L"de",     L"coração", L"sou",
        L"do",  L"clube",    L"tantas", L"vezes",   L"campeão"};
    REQUIRE(vectorsAreEqual(expectedReturn1, splitStringContentInWords(str1)));

    std::wstring str2 =
        L"O objetivo deste trabalho é utilizar o desenvolvimento "
        "orientado a testes";
    std::vector<std::wstring> expectedReturn2 = {
        L"O", L"objetivo",        L"deste",     L"trabalho", L"é",     L"utilizar",
        L"o", L"desenvolvimento", L"orientado", L"a",        L"testes"};
    REQUIRE(vectorsAreEqual(expectedReturn2, splitStringContentInWords(str2)));

    std::wstring str3 = L"Este texto é o texto que será utilizado";
    std::vector<std::wstring> expectedReturn3 = {
        L"Este", L"texto", L"é", L"o", L"texto", L"que", L"será", L"utilizado",
    };
    REQUIRE(vectorsAreEqual(expectedReturn3, splitStringContentInWords(str3)));

    std::wstring str4 = L"Bom bom       dia";
    std::vector<std::wstring> expectedReturn4 = {L"Bom", L"bom", L"dia"};
    REQUIRE(vectorsAreEqual(expectedReturn4, splitStringContentInWords(str4)));

    std::wstring str5 = L"German    Ezequiel Cano \n  \n Recalde";
    std::vector<std::wstring> expectedReturn5 = {
        L"German",
        L"Ezequiel",
        L"Cano",
        L"Recalde",
    };
    REQUIRE(vectorsAreEqual(expectedReturn5, splitStringContentInWords(str5)));
}

TEST_CASE("Should not contain space or break line in a single word",
          "[splitStringContentInWords]") {
    std::vector<std::wstring> words;
    auto checkIfNotContainSpaceAndBreakLine = [](std::vector<std::wstring> &v) {
        bool flag = true;

        for (std::wstring s : v) {
            flag &= (s.find(L' ') == s.npos) && (s.find(L'\n') == s.npos);
        }
        return flag;
    };

    std::wstring str1 =
        L"Sou tricolor de coração\n sou do clube tantas vezes campeão";
    words = splitStringContentInWords(str1);
    REQUIRE(checkIfNotContainSpaceAndBreakLine(words));

    std::wstring str2 =
        L"O objetivo deste trabalho é utilizar o desenvolvimento "
        "orientado a testes";
    words = splitStringContentInWords(str2);
    REQUIRE(checkIfNotContainSpaceAndBreakLine(words));

    std::wstring str3 = L"Este texto é o texto que será utilizado";
    words = splitStringContentInWords(str3);
    REQUIRE(checkIfNotContainSpaceAndBreakLine(words));

    std::wstring str4 = L"Bom bom       dia";
    words = splitStringContentInWords(str4);
    REQUIRE(checkIfNotContainSpaceAndBreakLine(words));

    std::wstring str5 = L"German    Ezequiel Cano \n   \n Recalde";
    words = splitStringContentInWords(str5);
    REQUIRE(checkIfNotContainSpaceAndBreakLine(words));
}

TEST_CASE("Should count the frequency of each word in the input file",
          "[getWordsCount]") {
    auto checkWordsCount = [](const std::vector<std::pair<std::wstring, int>> &v,
                              WordsCounter &counter) {
        bool flag = true;
        for (std::pair<std::wstring, int> p : v) {
            flag &= counter.getWordCount(p.first) == p.second;
        }

        flag &= (static_cast<int>(v.size()) == counter.size());

        return flag;
    };

    std::string content1 = "Fluminense Futebol Clube";
    writeContentInInputFile(content1);
    WordsCounter count1 = getWordsCount();
    std::vector<std::pair<std::wstring, int>> expectedResult1 = {
        {L"Fluminense", 1},
        {L"Futebol", 1},
        {L"Clube", 1},
    };
    REQUIRE(checkWordsCount(expectedResult1, count1));

    std::string content2 = "Este texto é o texto que será utilizado";
    writeContentInInputFile(content2);
    WordsCounter count2 = getWordsCount();
    std::vector<std::pair<std::wstring, int>> expectedResult2 = {
        {L"Este", 1}, {L"texto", 2}, {L"é", 1},         {L"o", 1},
        {L"que", 1},  {L"será", 1},  {L"utilizado", 1},
    };
    REQUIRE(checkWordsCount(expectedResult2, count2));

    std::string content3 = "zero oito zero quatro dois zero zero cinco";
    writeContentInInputFile(content3);
    WordsCounter count3 = getWordsCount();
    std::vector<std::pair<std::wstring, int>> expectedResult3 = {
        {L"zero", 4}, {L"oito", 1}, {L"dois", 1}, {L"quatro", 1}, {L"cinco", 1},
    };
    REQUIRE(checkWordsCount(expectedResult3, count3));

    std::string content4 = "Bom bom bOm boM bom BoM";
    writeContentInInputFile(content4);
    WordsCounter count4 = getWordsCount();
    std::vector<std::pair<std::wstring, int>> expectedResult4 = {
        {L"bom", 2}, {L"Bom", 1}, {L"boM", 1}, {L"bOm", 1}, {L"BoM", 1},
    };
    REQUIRE(checkWordsCount(expectedResult4, count4));

    clearInputFile();
}

TEST_CASE(
    "Should mantain the words frequency sorted lexicographically by the words",
    "[getWordsCount]") {
    auto checkIfIsSorted = [](std::vector<std::wstring> &v,
                              WordsCounter counter) {
        bool flag = true;
        int ithwstring = 0;
        for (std::pair<std::wstring, int> p : counter.getSortedValues()) {
            flag &= p.first == v[ithwstring];
            ithwstring++;
        }

        flag &= (static_cast<int>(v.size()) == counter.size());

        return flag;
    };

    std::vector<std::wstring> expectedOrder;
    std::string data;

    data = "fluminense é o maior do brasil";
    writeContentInInputFile(data);
    expectedOrder = {L"brasil", L"do", L"é", L"fluminense", L"maior", L"o"};

    REQUIRE(checkIfIsSorted(expectedOrder, getWordsCount()));
}
