#include <iostream>
#include <cassert>
#include <map>
#include <algorithm>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"

int getLeastFuelCommonPosition(std::vector<int> initialStatePositions, bool incrementingFuelCount)
{
    int minElement = *std::min_element(initialStatePositions.begin(), initialStatePositions.end());
    int maxElement = *std::max_element(initialStatePositions.begin(), initialStatePositions.end());

    std::map<int, int> fuelAndCommonPosition;

    for (int position = minElement; position <= maxElement; position++)
    {
        int totalFuel = 0;
        for (int currentPosition : initialStatePositions)
        {
            if (incrementingFuelCount)
            {
                totalFuel += (std::abs(currentPosition - position) * (std::abs(currentPosition - position) + 1)) / 2;
            }
            else
            {
                totalFuel += std::abs(currentPosition - position);
            }
        }
        fuelAndCommonPosition[totalFuel] = position;
    }

    return fuelAndCommonPosition.begin()->first;
}

int main(void)
{
    std::vector<int> initialStatePositionsTest = VectorOperations::stringVectorToIntVector(StringOperations::splitString("16,1,2,0,4,2,7,1,2,14", ","));
    assert(getLeastFuelCommonPosition(initialStatePositionsTest, false) == 37);

    InputFile inputFile("InputFiles/day07.txt");
    std::vector<int> initialStatePositions = inputFile.getContentAsInt(",");
    std::cout << "Day 7, puzzle 1: " << getLeastFuelCommonPosition(initialStatePositions, false) << std::endl;

    assert(getLeastFuelCommonPosition(initialStatePositionsTest, true) == 168);
    std::cout << "Day 7, puzzle 2: " << getLeastFuelCommonPosition(initialStatePositions, true) << std::endl;
}
