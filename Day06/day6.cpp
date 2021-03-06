#include <iostream>
#include <cassert>
#include <map>
#include <chrono>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"


unsigned long getAmount(std::vector<int> initialState, int daysToSimulate)
{
    std::map<int, std::map<int, unsigned long>> dayAndFishes;
    std::map<int, unsigned long> fishes;
    unsigned long amount = 0;
    for (int fish : initialState)
    {
        fishes[fish] += 1;
    }
    dayAndFishes[0] = fishes;
    for (int day = 1; day <= daysToSimulate; day++)
    {
        std::map<int, unsigned long> newFishes;
        newFishes[6] = fishes[0];
        newFishes[8] = fishes[0];
        for (int daysToReproduce = 0; daysToReproduce < 8; daysToReproduce++)
        {
            newFishes[daysToReproduce] += fishes[daysToReproduce + 1];
        }
        fishes = newFishes;
        dayAndFishes[day] = fishes;
        amount = 0;
        for (int i = 0; i <= 8; i++)
        {
            amount += dayAndFishes[day][i];
        }
    }
    
    return amount;
}

int main(void)
{
    std::vector<int> initialStateFishesTest = VectorOperations::stringVectorToIntVector(StringOperations::splitString("3,4,3,1,2", ","));
    assert(getAmount(initialStateFishesTest, 80) == 5934);

    InputFile inputFile("InputFiles/day06.txt");
    std::vector<int> initialStateFishes = inputFile.getContentAsInt(",");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 1: " << std::flush << getAmount(initialStateFishes, 80) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(getAmount(initialStateFishesTest, 256) == 26984457539);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 2: " << std::flush << getAmount(initialStateFishes, 256) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
