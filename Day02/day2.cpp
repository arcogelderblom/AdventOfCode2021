#include <iostream>
#include <cassert>

#include "inputfile.hpp"
#include "submarine.hpp"

int main(void)
{
    std::vector<std::string> testInput {"forward 5", "down 5", "forward 8", "up 3", "down 8", "forward 2"};
    Submarine testInputSubmarine;
    testInputSubmarine.travel(testInput);
    assert(testInputSubmarine.getHorizontalPosition() * testInputSubmarine.getDepth() == 150);

    InputFile inputFile("InputFiles/day02.txt");
    std::vector<std::string> commands = inputFile.getContentAsString("\n");
    Submarine submarine;
    submarine.travel(commands);
    std::cout << "Day 2, puzzle 1: " << submarine.getHorizontalPosition() * submarine.getDepth() << std::endl;
    
    Submarine testInputSubmarine2;
    testInputSubmarine2.travel(testInput, true);
    assert(testInputSubmarine2.getHorizontalPosition() * testInputSubmarine2.getDepth() == 900);

    Submarine submarine2;
    submarine2.travel(commands, true);
    std::cout << "Day 2, puzzle 2: " << submarine2.getHorizontalPosition() * submarine2.getDepth() << std::endl;
}