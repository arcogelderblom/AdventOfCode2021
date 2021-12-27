#include <iostream>
#include <chrono>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"

typedef std::pair<int,int> Coordinate;

std::vector<int> getPossibleRisks(std::vector<std::string> riskLevelMap, Coordinate startCoordinate, int depth, int currentDepth = 0)
{
    if (currentDepth == depth)
    {
        return std::vector<int> { 0 };
    }
    std::vector<int> result;
    Coordinate coordinateMoveRight = std::make_pair(startCoordinate.first, startCoordinate.second + 1);
    Coordinate coordinateMoveDown = std::make_pair(startCoordinate.first + 1, startCoordinate.second);
    if (coordinateMoveRight.second < riskLevelMap.size())
    {
        int currentRiskLevel = riskLevelMap[startCoordinate.first][startCoordinate.second] - '0';
        std::vector<int> riskLevelsToAdd = getPossibleRisks(riskLevelMap, coordinateMoveRight, depth, currentDepth+1);
        for (int riskLevelToAdd : riskLevelsToAdd)
        {
            result.push_back(currentRiskLevel + riskLevelToAdd);
        }
    }
    if (coordinateMoveDown.first < riskLevelMap[0].size())
    {
        int currentRiskLevel = riskLevelMap[startCoordinate.first][startCoordinate.second] - '0';
        std::vector<int> riskLevelsToAdd = getPossibleRisks(riskLevelMap, coordinateMoveDown, depth, currentDepth+1);
        // std::cout << currentRiskLevel << std::endl;
        for (int riskLevelToAdd : riskLevelsToAdd)
        {
            result.push_back(currentRiskLevel + riskLevelToAdd);
        }
    }
    return result; 
}

int findPathLowestRisk(std::vector<std::string> riskLevelMap)
{
    int risk = 0;
    Coordinate currentPosition = std::make_pair(0, 0);
    std::cout << riskLevelMap[currentPosition.first][currentPosition.second] << std::endl;
    Coordinate endPosition = std::make_pair<int,int>(riskLevelMap.size() - 1, riskLevelMap[0].size() - 1);
    while (currentPosition != endPosition)
    {
        if (std::make_pair(currentPosition.first + 1, currentPosition.second) == endPosition)
        {
            currentPosition = endPosition;
            risk += riskLevelMap[currentPosition.first][currentPosition.second] - '0';
        }
        else if (std::make_pair(currentPosition.first, currentPosition.second + 1) == endPosition)
        {
            currentPosition = endPosition;
            risk += riskLevelMap[currentPosition.first][currentPosition.second] - '0';
        }

        if (currentPosition.first < riskLevelMap[0].size() - 1 && currentPosition.second < riskLevelMap.size() - 1)
        {
            Coordinate coordinateMoveRight = std::make_pair(currentPosition.first, currentPosition.second + 1);
            Coordinate coordinateMoveDown = std::make_pair(currentPosition.first + 1, currentPosition.second);
            std::vector<int> possibleRisksRight = getPossibleRisks(riskLevelMap, coordinateMoveRight, 3);
            std::vector<int> possibleRiskDown = getPossibleRisks(riskLevelMap, coordinateMoveDown, 3);
            
            std::sort(possibleRisksRight.begin(), possibleRisksRight.end());
            std::sort(possibleRiskDown.begin(), possibleRiskDown.end());
            if (possibleRisksRight < possibleRiskDown)
            {
                risk += riskLevelMap[coordinateMoveRight.first][coordinateMoveRight.second] - '0';
                currentPosition = coordinateMoveRight;
            }
            else 
            {
                risk += riskLevelMap[coordinateMoveDown.first][coordinateMoveDown.second] - '0';
                currentPosition = coordinateMoveDown;
            }
        }
        else if (currentPosition.first < riskLevelMap[0].size() - 1 && currentPosition.second == riskLevelMap.size() - 1)
        {
            Coordinate coordinateMoveDown = std::make_pair(currentPosition.first + 1, currentPosition.second);
            risk += riskLevelMap[coordinateMoveDown.first][coordinateMoveDown.second] - '0';
            currentPosition = coordinateMoveDown;
        }
        else if (currentPosition.first == riskLevelMap[0].size() - 1 && currentPosition.second < riskLevelMap.size() - 1)
        {
            Coordinate coordinateMoveRight = std::make_pair(currentPosition.first, currentPosition.second + 1);
            risk += riskLevelMap[coordinateMoveRight.first][coordinateMoveRight.second] - '0';
            currentPosition = coordinateMoveRight;   
        }
        if ((currentPosition.first < riskLevelMap[0].size() && currentPosition.second < riskLevelMap.size()) ||
           (currentPosition.first < riskLevelMap[0].size() && currentPosition.second == riskLevelMap.size() - 1) ||
           (currentPosition.first == riskLevelMap[0].size() - 1 && currentPosition.second < riskLevelMap.size()))
        {
            std::cout << riskLevelMap[currentPosition.first][currentPosition.second] << std::endl;
        }
    }
    return risk;
}

int main(void)
{
    std::vector<std::string> testInput = StringOperations::splitString("1163751742\n1381373672\n2136511328\n3694931569\n7463417111\n1319128137\n1359912421\n3125421639\n1293138521\n2311944581", "\n");
    //assert(findPathLowestRisk(testInput) == 40);
    
    InputFile inputFile("InputFiles/day15.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
//    std::cout << "Day 15, puzzle 1: " << std::flush << findPathLowestRisk(input) << " <-- NOT YET FINISHED..." << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    // assert(getResult(testPolymerTemplate, testPairInsertionRules, 40) == 2188189693529);
    // t_begin = std::chrono::high_resolution_clock::now();    
    // std::cout << "Day 15, puzzle 2: " << getResult(polymerTemplate, pairInsertionRules, 40) << std::endl;
    // t_end = std::chrono::high_resolution_clock::now();
    // std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
