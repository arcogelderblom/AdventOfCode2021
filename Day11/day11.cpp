#include <iostream>
#include <map>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"

void simulateSteps(std::vector< std::vector<int> >& energyLevelMap, int& totalFlashes, int steps)
{
    for (int step = 0; step < steps; step++)
    {
        // do all + 1 energy
        for (int y = 0; y < energyLevelMap.size(); y++)
        {
            for (int x = 0; x < energyLevelMap[y].size(); x++)
            {
                energyLevelMap[y][x] = energyLevelMap[y][x] + 1;
            }
        }

        // check which positions to visit
        std::vector< std::pair<int, int> > positionsToVisit;
        for (int y = 0; y < energyLevelMap.size(); y++)
        {
            for (int x = 0; x < energyLevelMap[y].size(); x++)
            {
                if (energyLevelMap[y][x] > 9)
                {
                    positionsToVisit.push_back(std::make_pair(y,x));
                }
            }
        }
        // go visit positions, ensure positions are only visited once because of only one flash
        
        while (!positionsToVisit.empty())
        {
            std::pair<int, int> currentPosition = positionsToVisit.front();
            positionsToVisit.erase(positionsToVisit.begin());
            auto it = std::unique(positionsToVisit.begin(), positionsToVisit.end());
            positionsToVisit.resize(std::distance(positionsToVisit.begin(), it));

            if (currentPosition.first != 0)
            {
                energyLevelMap[currentPosition.first- 1][currentPosition.second] = energyLevelMap[currentPosition.first- 1][currentPosition.second] + 1;
                if (energyLevelMap[currentPosition.first- 1][currentPosition.second] == 10)
                {
                    std::pair<int, int> positionToAdd = std::make_pair(currentPosition.first- 1, currentPosition.second);
                    positionsToVisit.push_back(positionToAdd);
                }
                if (currentPosition.second != energyLevelMap[currentPosition.first].size() - 1)
                {
                    energyLevelMap[currentPosition.first- 1][currentPosition.second + 1] = energyLevelMap[currentPosition.first- 1][currentPosition.second + 1] + 1;
                    if (energyLevelMap[currentPosition.first- 1][currentPosition.second + 1] == 10)
                    {
                        std::pair<int, int> positionToAdd = std::make_pair(currentPosition.first- 1, currentPosition.second + 1);
                        positionsToVisit.push_back(positionToAdd);
                    }
                }
                if (currentPosition.second != 0)
                {
                    energyLevelMap[currentPosition.first - 1][currentPosition.second - 1] = energyLevelMap[currentPosition.first - 1][currentPosition.second - 1] + 1;
                    if (energyLevelMap[currentPosition.first - 1][currentPosition.second - 1] == 10)
                    {
                        std::pair<int, int> positionToAdd = std::make_pair(currentPosition.first - 1, currentPosition.second - 1);
                        positionsToVisit.push_back(positionToAdd);
                    }
                }
            }
            if (currentPosition.second != energyLevelMap[currentPosition.first].size() - 1)
            {
                energyLevelMap[currentPosition.first][currentPosition.second + 1] = energyLevelMap[currentPosition.first][currentPosition.second + 1] + 1;
                if (energyLevelMap[currentPosition.first][currentPosition.second + 1] == 10)
                {
                    std::pair<int, int> positionToAdd = std::make_pair(currentPosition.first, currentPosition.second + 1);
                    positionsToVisit.push_back(positionToAdd);
                }
            }
            if (currentPosition.second != 0)
            {
                energyLevelMap[currentPosition.first][currentPosition.second - 1] = energyLevelMap[currentPosition.first][currentPosition.second - 1] + 1;
                if (energyLevelMap[currentPosition.first][currentPosition.second - 1] == 10)
                {
                    std::pair<int, int> positionToAdd = std::make_pair(currentPosition.first, currentPosition.second - 1);
                    positionsToVisit.push_back(positionToAdd);
                }
            }
            if (currentPosition.first != energyLevelMap.size() - 1)
            {
                energyLevelMap[currentPosition.first + 1][currentPosition.second] = energyLevelMap[currentPosition.first + 1][currentPosition.second] + 1;
                if (energyLevelMap[currentPosition.first + 1][currentPosition.second] == 10)
                {
                    std::pair<int, int> positionToAdd = std::make_pair(currentPosition.first + 1, currentPosition.second);
                    positionsToVisit.push_back(positionToAdd);
                }
                if (currentPosition.second != energyLevelMap[currentPosition.first].size() - 1)
                {
                    energyLevelMap[currentPosition.first + 1][currentPosition.second + 1] = energyLevelMap[currentPosition.first + 1][currentPosition.second + 1] + 1;
                    if (energyLevelMap[currentPosition.first + 1][currentPosition.second + 1] == 10)
                    {
                        std::pair<int, int> positionToAdd = std::make_pair(currentPosition.first + 1, currentPosition.second + 1);
                        positionsToVisit.push_back(positionToAdd);
                    }
                }
                if (currentPosition.second != 0)
                {
                    energyLevelMap[currentPosition.first + 1][currentPosition.second - 1] = energyLevelMap[currentPosition.first + 1][currentPosition.second - 1] + 1;
                    if (energyLevelMap[currentPosition.first + 1][currentPosition.second - 1] == 10)
                    {
                        std::pair<int, int> positionToAdd = std::make_pair(currentPosition.first + 1, currentPosition.second - 1);
                        positionsToVisit.push_back(positionToAdd);
                    }
                }
            }
        }

        // count flashes and set energy to 0
        int flashes = 0;
        for (int y = 0; y < energyLevelMap.size(); y++)
        {
            for (int x = 0; x < energyLevelMap[y].size(); x++)
            {
                if (energyLevelMap[y][x] > 9)
                {
                    energyLevelMap[y][x] = 0;
                    flashes++;
                }
            }
        }
        totalFlashes += flashes;
    }
}

int getFirstStepAllFlash(std::vector< std::vector<int> >& energyLevelMap, int& totalFlashes, int startStep)
{
    int prevTotalFlashes = totalFlashes;
    int deltaForSynchronizedFlash = energyLevelMap.size() * energyLevelMap[0].size();
    int currentStep = startStep;
    while (totalFlashes - prevTotalFlashes != deltaForSynchronizedFlash)
    {
        prevTotalFlashes = totalFlashes;
        simulateSteps(energyLevelMap, totalFlashes, 1);
        currentStep++;
    }
    return currentStep;
}

int main(void)
{
    std::vector< std::vector<int> > test = VectorOperations::stringVectorToSeparatedIntVector(StringOperations::splitString("11111\n19991\n19191\n19991\n11111", "\n"));
    int totalFlashesTestEasy = 0;
    simulateSteps(test, totalFlashesTestEasy, 2);

    std::vector< std::vector<int> > testMap = VectorOperations::stringVectorToSeparatedIntVector(StringOperations::splitString("5483143223\n2745854711\n5264556173\n6141336146\n6357385478\n4167524645\n2176841721\n6882881134\n4846848554\n5283751526", "\n"));
    int totalFlashesTest = 0;
    simulateSteps(testMap, totalFlashesTest, 100);
    assert(totalFlashesTest == 1656);
    
    InputFile inputFile("InputFiles/day11.txt");
    std::vector< std::vector<int> > input = VectorOperations::stringVectorToSeparatedIntVector(inputFile.getContentAsString("\n"));
    int totalFlashes = 0;
    simulateSteps(input, totalFlashes, 100);
    std::cout << "Day 11, puzzle 1: " << totalFlashes << std::endl;

    assert(getFirstStepAllFlash(testMap, totalFlashesTest, 100) == 195);
    std::cout << "Day 11, puzzle 2: " << getFirstStepAllFlash(input, totalFlashes, 100) << std::endl;
}
