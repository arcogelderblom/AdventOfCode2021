#include <iostream>
#include <vector>

#include "inputfile.hpp"

int getIncreaseCount(std::vector<int> measurements) 
{
    int increaseCount = 0;
    for (int i = 0; i < measurements.size() - 1; i++) {
        int first = measurements[i];
        int second = measurements[i+1];
        if (second > first) {
            increaseCount++;
        }    
    }
    return increaseCount;
}

int getIncreaseCountSum(std::vector<int> measurements) 
{
    int increaseCount = 0;
    for (int i = 0; i < measurements.size() - 3; i++) {
        int first = measurements[i] + measurements[i+1] + measurements[i+2];
        int second = measurements[i+1] + measurements[i+2] + measurements[i+3];
        if (second > first) {
            increaseCount++;
        }    
    }
    return increaseCount;
}

int main(void) 
{
    std::vector<int> testInput {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
    assert(getIncreaseCount(testInput) == 7);

    InputFile inputFile("InputFiles/day1.txt");
    std::vector<int> measurements = inputFile.getContentAsInt("\n");
    std::cout << "Day 1, puzzle 1: " << getIncreaseCount(measurements) << std::endl;

    assert(getIncreaseCountSum(testInput) == 5);
    std::cout << "Day 1, puzzle 2: " << getIncreaseCountSum(measurements) << std::endl;
}