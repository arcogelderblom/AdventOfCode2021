#include <iostream>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"
#include "bingo.hpp"

int main(void)
{
    std::string numbersDrawnTestString = "7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1";
    std::vector<int> numbersDrawnTest = VectorOperations::stringVectorToIntVector(StringOperations::splitString(numbersDrawnTestString, ","));
    std::vector<std::string> bingoCardsTest = {"22 13 17 11  0\n 8  2 23  4 24\n21  9 14 16  7\n 6 10  3 18  5\n 1 12 20 15 19"," 3 15  0  2 22\n 9 18 13 17  5\n19  8  7 25 23\n20 11 10 24  4\n14 21 16 12  6", "14 21 17 24  4\n10 16 15  9 19\n18  8 23 26 20\n22 11 13  6  5\n 2  0 12  3  7"};
    Bingo testGame(bingoCardsTest);
    assert(testGame.play(numbersDrawnTest) == 4512);

    InputFile inputFile("InputFiles/day04.txt");
    std::vector<std::string> inputFileContent = inputFile.getContentAsString("\n\n");
    std::vector<int> numbersDrawn = VectorOperations::stringVectorToIntVector(StringOperations::splitString(inputFileContent[0], ","));
    inputFileContent.erase(inputFileContent.begin());
    std::vector<std::string> bingoCards = inputFileContent;

    Bingo game(bingoCards);
    int finalScore = game.play(numbersDrawn);
    std::cout << "Day 4, puzzle 1: " << finalScore << std::endl;

    Bingo testGame2(bingoCardsTest);
    assert(testGame2.play(numbersDrawnTest, true) == 1924);

    Bingo game2(bingoCards);
    finalScore = game2.play(numbersDrawn, true);
    std::cout << "Day 4, puzzle 2: " << finalScore << std::endl;
}