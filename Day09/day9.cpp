#include <iostream>
#include <map>
#include <numeric>
#include <algorithm>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"

std::map<std::pair<int, int> , int> getAdjacentPositionsWithValue(std::vector<std::string> map, std::pair<int,int> startPoint)
{
    std::map<std::pair<int, int> , int> result;
    if (startPoint.first != 0)
    {
        std::pair<int,int> current = std::make_pair(startPoint.second, startPoint.first - 1);
        result[std::make_pair(current.second, current.first)] = map[current.first][current.second] - '0';
    }
    if (startPoint.second != 0)
    {
        std::pair<int,int> current = std::make_pair(startPoint.second - 1, startPoint.first);
        result[std::make_pair(current.second, current.first)] = map[current.first][current.second] - '0';
    }
    if (startPoint.first != map[startPoint.second].size() - 1)
    {
        std::pair<int,int> current = std::make_pair(startPoint.second, startPoint.first + 1);
        result[std::make_pair(current.second, current.first)] = map[current.first][current.second] - '0';
    }
    if (startPoint.second != map.size() - 1)
    {
        std::pair<int,int> current = std::make_pair(startPoint.second + 1, startPoint.first);
        result[std::make_pair(current.second, current.first)] = map[current.first][current.second] - '0';
    }
    return result;
}

std::vector< std::pair<int,int> > findLowPointsIndexes(std::vector<std::string> map)
{
    std::vector< std::pair<int,int> > result;
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            std::vector<int> adjacentHeights;
            for (std::pair< std::pair<int,int>, int > adjacentPositionWithValue : getAdjacentPositionsWithValue(map, std::make_pair(x, y)))
            {
                adjacentHeights.push_back(adjacentPositionWithValue.second);
            }
            int currentHeight = map[y][x] - '0';
            if (std::count_if(adjacentHeights.begin(), adjacentHeights.end(), [&](const int adjacentHeight){ return currentHeight < adjacentHeight; }) == adjacentHeights.size())
            {
                result.push_back(std::make_pair(x, y));
            }
        }
    }
    return result;
}

unsigned long getSumRiskLevels(std::vector<std::string> map)
{
    unsigned long sum = 0;
    for (std::pair<int, int> lowPoint : findLowPointsIndexes(map))
    {
        sum += 1 + (map[lowPoint.second][lowPoint.first] - '0');
    }
    
    return sum;
}

int getBasinSize(std::vector<std::string> map, std::pair<int,int> startPoint)
{
    std::vector< std::pair<int,int> > pointsInBasin;
    pointsInBasin.push_back(startPoint);
    std::vector< std::pair<int,int> > unvisitedAdjacentPoints;
    unvisitedAdjacentPoints.push_back(startPoint);
    while (unvisitedAdjacentPoints.size() > 0)
    {
        std::map<std::pair<int, int> , int> adjacentPointsWithValue = getAdjacentPositionsWithValue(map, unvisitedAdjacentPoints.front());
        int currentValue = map[unvisitedAdjacentPoints.front().second][unvisitedAdjacentPoints.front().first] - '0';
        unvisitedAdjacentPoints.erase(unvisitedAdjacentPoints.begin());
        for (std::pair< std::pair<int,int>, int > adjacentPointWithValue : adjacentPointsWithValue)
        {
            if (currentValue + 1 == adjacentPointWithValue.second &&  adjacentPointWithValue.second != 9)
            {
                if (std::find(pointsInBasin.begin(), pointsInBasin.end(), adjacentPointWithValue.first) == pointsInBasin.end())
                {
                    unvisitedAdjacentPoints.push_back(adjacentPointWithValue.first);
                    pointsInBasin.push_back(adjacentPointWithValue.first);
                }
            }
        }
        auto it = std::unique(unvisitedAdjacentPoints.begin(), unvisitedAdjacentPoints.end());
        unvisitedAdjacentPoints.resize(std::distance(unvisitedAdjacentPoints.begin(), it));
    }

    auto it = std::unique(pointsInBasin.begin(), pointsInBasin.end());
    pointsInBasin.resize(std::distance(pointsInBasin.begin(), it));
    
    return pointsInBasin.size();
}

unsigned long getMultipliedThreeLargestBasins(std::vector<std::string> map)
{
    std::vector<int> largestBasinSizes;
    for (std::pair<int, int> lowPoint : findLowPointsIndexes(map))
    {
        int basinSize = getBasinSize(map, lowPoint);
        
        if (largestBasinSizes.size() < 3)
        {
            largestBasinSizes.push_back(basinSize);
        }
        else if (largestBasinSizes.front() < basinSize)
        {
            largestBasinSizes[0] = basinSize;
        }
        std::sort(largestBasinSizes.begin(), largestBasinSizes.end());
    }

    unsigned long result = 1;
    for (int basinSize : largestBasinSizes)
    {
        result *= basinSize;
    }
    return result;
}

int main(void)
{
    std::vector<std::string> testMap = StringOperations::splitString("2199943210\n3987894921\n9856789892\n8767896789\n9899965678", "\n");
    assert(getSumRiskLevels(testMap) == 15);
    
    InputFile inputFile("InputFiles/day09.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    std::cout << "Day 9, puzzle 1: " << getSumRiskLevels(input) << std::endl;

    assert(getMultipliedThreeLargestBasins(testMap) == 1134);
    std::cout << "Day 9, puzzle 2: " << getMultipliedThreeLargestBasins(input) << " <-- NOT YET CORRECT" << std::endl;
}
