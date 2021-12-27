#include <iostream>
#include <chrono>
#include <map>
#include <tuple>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"

typedef std::tuple<int, int, int> Coordinate;

void executeRebootStep(std::map<Coordinate, bool>& start, std::string rebootStep, bool puzzle1)
{
    std::string instruction = StringOperations::splitString(rebootStep, " ")[0];
    bool on = (instruction == "on");
    std::string xStartAndEnd = StringOperations::splitString(StringOperations::splitString(rebootStep, " ")[1], ",")[0].substr(2);
    std::string yStartAndEnd = StringOperations::splitString(StringOperations::splitString(rebootStep, " ")[1], ",")[1].substr(2);
    std::string zStartAndEnd = StringOperations::splitString(StringOperations::splitString(rebootStep, " ")[1], ",")[2].substr(2);
    int xMin = std::stoi(StringOperations::splitString(xStartAndEnd, "..")[0]);
    int xMax = std::stoi(StringOperations::splitString(xStartAndEnd, "..")[1]);
    int yMin = std::stoi(StringOperations::splitString(yStartAndEnd, "..")[0]);
    int yMax = std::stoi(StringOperations::splitString(yStartAndEnd, "..")[1]);
    int zMin = std::stoi(StringOperations::splitString(zStartAndEnd, "..")[0]);
    int zMax = std::stoi(StringOperations::splitString(zStartAndEnd, "..")[1]);

    if (puzzle1)
    {
        if (xMin < -50)
        {
            xMin = -50;
        }
        if (yMin < -50)
        {
            yMin = -50;
        }
        if (zMin < -50)
        {
            zMin = -50;
        }
        if (xMax > 50)
        {
            xMax = 50;
        }
        if (yMax > 50)
        {
            yMax = 50;
        }
        if (zMax > 50)
        {
            zMax = 50;
        }
    }
    for (int x = xMin; x <= xMax; x++)
    {
        for (int y = yMin; y <= yMax; y++)
        {
            for (int z = zMin; z <= zMax; z++)
            {
                start[std::make_tuple(x, y, z)] = on;
            }
        }
    }
}

long long getLitCubesInSector(std::vector<std::string> rebootSteps, bool puzzle1 = false)
{
    std::map<Coordinate, bool> litCubes;

    int currentRebootStepNum = 1;
    for (std::string rebootStep : rebootSteps)
    {
        std::cout << "Current reboot step: " << currentRebootStepNum << "\\" << rebootSteps.size() << ": " << rebootStep << std::endl;
        executeRebootStep(litCubes, rebootStep, puzzle1);
        currentRebootStepNum++;
    }
    
    return std::count_if(litCubes.begin(), litCubes.end(), [](std::pair<Coordinate, bool> item){ return item.second == true; });
}

int main(void)
{
    std::vector<std::string> testInput = StringOperations::splitString("on x=-20..26,y=-36..17,z=-47..7\non x=-20..33,y=-21..23,z=-26..28\non x=-22..28,y=-29..23,z=-38..16\non x=-46..7,y=-6..46,z=-50..-1\non x=-49..1,y=-3..46,z=-24..28\non x=2..47,y=-22..22,z=-23..27\non x=-27..23,y=-28..26,z=-21..29\non x=-39..5,y=-6..47,z=-3..44\non x=-30..21,y=-8..43,z=-13..34\non x=-22..26,y=-27..20,z=-29..19\noff x=-48..-32,y=26..41,z=-47..-37\non x=-12..35,y=6..50,z=-50..-2\noff x=-48..-32,y=-32..-16,z=-15..-5\non x=-18..26,y=-33..15,z=-7..46\noff x=-40..-22,y=-38..-28,z=23..41\non x=-16..35,y=-41..10,z=-47..6\noff x=-32..-23,y=11..30,z=-14..3\non x=-49..-5,y=-3..45,z=-29..18\noff x=18..30,y=-20..-8,z=-3..13\non x=-41..9,y=-7..43,z=-33..15\non x=-54112..-39298,y=-85059..-49293,z=-27449..7877\non x=967..23432,y=45373..81175,z=27513..53682", "\n");
    assert(getLitCubesInSector(testInput, true) == 590784);
    
    InputFile inputFile("InputFiles/day22.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 22, puzzle 1: " << std::flush << getLitCubesInSector(input, true) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();    
   // std::cout << "Day 22, puzzle 2: " << std::flush << getLitCubesInSector(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}