#include <iostream>
#include <map>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"

std::vector< std::vector<std::string> > findAllPaths(std::vector< std::vector<std::string> > roughMap, bool visitSmallCaveTwice = false)
{
    std::map< std::string, std::vector<std::string> > options;
    for (std::vector<std::string> entry : roughMap)
    {
        if (entry[0] != "start" && entry[1] != "end")
        {
            options[entry[1]].push_back(entry[0]);
        }
        options[entry[0]].push_back(entry[1]);
    }

    std::vector<std::string> smallCaves;
    for (auto destination : options)
    {
        if (std::all_of(destination.first.begin(), destination.first.end(), [](unsigned char c){ return std::islower(c); }) && destination.first != "start" && destination.first != "end")
        {
            smallCaves.push_back(destination.first);
        }
    }
    
    std::vector< std::vector<std::string> > paths;
    std::vector< std::vector<std::string> > unfinishedPaths;
    std::vector<std::string> startPath = {"start"};
    unfinishedPaths.push_back(startPath);
    while (unfinishedPaths.size() > 0)
    {
        std::vector< std::vector<std::string> > deadEnds;
        std::vector< std::vector<std::string> > unfinishedPathsToAdd;
        int currentPathToHandle = 0;
        for (std::vector<std::string>& path : unfinishedPaths)
        {
            currentPathToHandle++;
            std::string currentPosition = path.back();
            if (options[currentPosition].size() > 1)
            {
                std::vector< std::vector<std::string> > copies(options[currentPosition].size() - 1, path);
                // must create copies
                for (int i = 1; i < options[currentPosition].size(); i++)
                {
                    if (std::all_of(options[currentPosition][i].begin(), options[currentPosition][i].end(), [](unsigned char c){ return std::isupper(c); }))
                    {
                        copies[i - 1].push_back(options[currentPosition][i]);
                        unfinishedPathsToAdd.push_back(copies[i-1]);
                    }
                    else if (std::find(copies[i-1].begin(), copies[i-1].end(), options[currentPosition][i]) == copies[i-1].end())
                    {
                        copies[i - 1].push_back(options[currentPosition][i]);
                        unfinishedPathsToAdd.push_back(copies[i-1]);
                    }
                    else if (visitSmallCaveTwice && std::count(path.begin(), path.end(), options[currentPosition][i]) == 1 && std::count_if(smallCaves.begin(), smallCaves.end(), [&](std::string destination){ return std::count(path.begin(), path.end(), destination) == 2; }) == 0 && std::find(smallCaves.begin(), smallCaves.end(), options[currentPosition][i]) != smallCaves.end())
                    {
                        copies[i - 1].push_back(options[currentPosition][i]);
                        unfinishedPathsToAdd.push_back(copies[i-1]);
                    }
                }
            }

            if (std::all_of(options[currentPosition][0].begin(), options[currentPosition][0].end(), [](unsigned char c){ return std::isupper(c); }))
            {
                path.push_back(options[currentPosition][0]);
            }
            else if (std::find(path.begin(), path.end(), options[currentPosition][0]) == path.end())
            {
                path.push_back(options[currentPosition][0]);
            }
            else if (visitSmallCaveTwice && std::count(path.begin(), path.end(), options[currentPosition][0]) == 1 && std::count_if(smallCaves.begin(), smallCaves.end(), [&](std::string destination){ return std::count(path.begin(), path.end(), destination) == 2; }) == 0 && std::find(smallCaves.begin(), smallCaves.end(), options[currentPosition][0]) != smallCaves.end())
            {
                path.push_back(options[currentPosition][0]);
            }
            else 
            {
                path.push_back(options[currentPosition][0]);
                deadEnds.push_back(path);
            }
        }
        
        unfinishedPaths.insert(unfinishedPaths.end(), unfinishedPathsToAdd.begin(), unfinishedPathsToAdd.end());
        
        // remove dead ends
        for (const std::vector<std::string> &  deadEnd : deadEnds)
        {
            unfinishedPaths.erase(std::remove(unfinishedPaths.begin(), unfinishedPaths.end(), deadEnd), unfinishedPaths.end());
        }

        // check for finished paths
        int oldPathsSize = paths.size();
        for (const std::vector<std::string> & path: unfinishedPaths)
        {
            if (path.back() == "end")
            {
                //finished path
                paths.push_back(path);
            }
        }
        
        if (paths.size() > oldPathsSize)
        {
            for (int i = oldPathsSize; i < paths.size(); i++)
            {
                unfinishedPaths.erase(std::remove(unfinishedPaths.begin(), unfinishedPaths.end(), paths[i]), unfinishedPaths.end());
            }
        }
    }

    return paths;
}

int main(void)
{
    std::vector< std::vector<std::string> > testInput1 = VectorOperations::splitVectorInSubVectors(StringOperations::splitString("start-A\nstart-b\nA-c\nA-b\nb-d\nA-end\nb-end", "\n"), "-");
    assert(findAllPaths(testInput1).size() == 10);

    std::vector< std::vector<std::string> > testInput2 = VectorOperations::splitVectorInSubVectors(StringOperations::splitString("dc-end\nHN-start\nstart-kj\ndc-start\ndc-HN\nLN-dc\nHN-end\nkj-sa\nkj-HN\nkj-dc", "\n"), "-");
    assert(findAllPaths(testInput2).size() == 19);

    std::vector< std::vector<std::string> > testInput3 = VectorOperations::splitVectorInSubVectors(StringOperations::splitString("fs-end\nhe-DX\nfs-he\nstart-DX\npj-DX\nend-zg\nzg-sl\nzg-pj\npj-he\nRW-he\nfs-DX\npj-RW\nzg-RW\nstart-pj\nhe-WI\nzg-he\npj-fs\nstart-RW", "\n"), "-");
    assert(findAllPaths(testInput3).size() == 226);
    
    InputFile inputFile("InputFiles/day12.txt");
    std::vector< std::vector<std::string> > input = VectorOperations::splitVectorInSubVectors(inputFile.getContentAsString("\n"), "-");
    std::cout << "Day 12, puzzle 1: " << findAllPaths(input).size() << std::endl;

    assert(findAllPaths(testInput1, true).size() == 36);
    assert(findAllPaths(testInput2, true).size() == 103);
    assert(findAllPaths(testInput3, true).size() == 3509);
    std::cout << "Day 12, puzzle 2: " << findAllPaths(input, true).size() << std::endl;
}