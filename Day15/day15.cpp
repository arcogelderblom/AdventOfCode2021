#include <iostream>
#include <chrono>
#include <tuple> 

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"

#define NO_PARENT std::make_pair(-1,-1)

typedef std::pair<int,int> Coordinate;

std::ostream& operator<<(std::ostream& os, const Coordinate& c)
{
    os << c.first << "," << c.second;
    return os;
}

struct Node
{
    Coordinate thisNodeCoordinate;
    Coordinate parentCoordinate;
    int globalScore; // how much to get here + how much until the end
    int localScore; // how much to get here
    Node(Coordinate _thisNodeCoordinate, Coordinate _parentCoordinate, int _globalScore,int _localScore) :
        thisNodeCoordinate(_thisNodeCoordinate),
        parentCoordinate(_parentCoordinate),
        globalScore(_globalScore),
        localScore(_localScore)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Node& n)
    {
        os << "Node coordinate: " << n.thisNodeCoordinate << " | ";
        os << "Node parent coordinate:  " << n.parentCoordinate << " | ";
        os << "Global score " << n.globalScore << " | ";
        os << "Local score " << n.localScore;
        return os;
    }
};

int calculateDistanceToEnd(Coordinate start, Coordinate end)
{
    return std::abs(end.first - start.first) + std::abs(end.second - start.second);
}

void visitNode(const Node& nodeToVisit, std::vector<Node>& allDiscoveredNodes, std::vector<std::pair<Coordinate, int>>& coordinatesToVisit, const std::vector<Coordinate>& visitedCoordinates, const Coordinate& endCoordinate, const std::vector<std::string>& riskLevelMap)
{
    Coordinate coordinateMoveUp = std::make_pair(nodeToVisit.thisNodeCoordinate.first - 1, nodeToVisit.thisNodeCoordinate.second);
    Coordinate coordinateMoveDown = std::make_pair(nodeToVisit.thisNodeCoordinate.first + 1, nodeToVisit.thisNodeCoordinate.second);
    Coordinate coordinateMoveLeft = std::make_pair(nodeToVisit.thisNodeCoordinate.first, nodeToVisit.thisNodeCoordinate.second - 1);
    Coordinate coordinateMoveRight = std::make_pair(nodeToVisit.thisNodeCoordinate.first, nodeToVisit.thisNodeCoordinate.second + 1);

    // check if it is possible to move to the desired position;
    std::vector<Coordinate> possibleCoordinates;
    if (coordinateMoveUp.first >= 0)
    {
        possibleCoordinates.push_back(coordinateMoveUp);
    }
    if (coordinateMoveDown.first < riskLevelMap[0].size())
    {
        possibleCoordinates.push_back(coordinateMoveDown);
    }
    if (coordinateMoveLeft.second >= 0)
    {
        possibleCoordinates.push_back(coordinateMoveLeft);
    }
    if (coordinateMoveRight.second < riskLevelMap.size())
    {
        possibleCoordinates.push_back(coordinateMoveRight);
    }

    for (const Coordinate& possibleCoordinate : possibleCoordinates)
    {
        if (possibleCoordinate != std::make_pair(0,0)) // we ignore the start node and end node
        {
            int distance = nodeToVisit.localScore + (riskLevelMap[possibleCoordinate.first][possibleCoordinate.second] - '0'); // calculated local
            // check if node is in vector already
            auto node = std::find_if(allDiscoveredNodes.begin(), allDiscoveredNodes.end(), [&](Node node){ return node.thisNodeCoordinate == possibleCoordinate; });
            if (node != allDiscoveredNodes.end())
            {
                // present, check if route is shorter
                if (distance < node->localScore)
                {
                    node->localScore = distance;
                    node->globalScore = calculateDistanceToEnd(possibleCoordinate, endCoordinate) + distance;
                    node->parentCoordinate = nodeToVisit.thisNodeCoordinate;
                    if (possibleCoordinate != endCoordinate)
                    {
                        auto coordinateToVisitInVector = std::find_if(coordinatesToVisit.begin(), coordinatesToVisit.end(), [&](std::pair<Coordinate, int> item){ return item.first == possibleCoordinate; });
                        if (coordinateToVisitInVector == coordinatesToVisit.end())
                        {
                            coordinatesToVisit.push_back(std::make_pair(possibleCoordinate, node->globalScore));
                        }
                        else
                        {
                            coordinateToVisitInVector->second = node->globalScore;
                        }    
                    
                    }
                }
            }
            else 
            {
                // not yet present, add
                Node newNode(possibleCoordinate, nodeToVisit.thisNodeCoordinate, calculateDistanceToEnd(possibleCoordinate, endCoordinate) + distance, distance);
                allDiscoveredNodes.push_back(newNode);
                if (possibleCoordinate != endCoordinate)
                {
                    coordinatesToVisit.push_back(std::make_pair(possibleCoordinate, newNode.globalScore));
                }
            }
        }
    }
}

void outputPath(std::vector<Node> allDiscoveredNodes, Coordinate endCoordinate)
{
    Coordinate currentPosition = endCoordinate;
    std::vector<Coordinate> path;
    while (currentPosition != std::make_pair(0, 0))
    {
        path.push_back(currentPosition);
        currentPosition = std::find_if(allDiscoveredNodes.begin(), allDiscoveredNodes.end(), [&](Node node){ return node.thisNodeCoordinate == currentPosition; })->parentCoordinate;

    }
    path.push_back(currentPosition);
    std::reverse(path.begin(), path.end());
    for (Coordinate point : path)
    {
        std::cout << point << " -> ";
        
    }
    std::cout << std::endl;
}

int findPathLowestRisk(std::vector<std::string> riskLevelMap)
{
    Coordinate currentPosition = std::make_pair(0, 0);
    Coordinate startPosition = currentPosition;
    Coordinate endPosition = std::make_pair<int,int>(riskLevelMap.size() - 1, riskLevelMap[0].size() - 1);

    Node startNode(startPosition, NO_PARENT, calculateDistanceToEnd(startPosition, endPosition), 0);
    std::vector<Node> allDiscoveredNodes;
    std::vector<std::pair<Coordinate, int>> coordinatesToVisit; // holds coordinates to visit and globalScore
    std::vector<Coordinate> visitedCoordinates;
    allDiscoveredNodes.push_back(startNode);
    coordinatesToVisit.push_back(std::make_pair(startNode.thisNodeCoordinate, startNode.globalScore));

    while (!coordinatesToVisit.empty())
    {
        // auto t_begin = std::chrono::high_resolution_clock::now();    
        Node nodeToVisit = *std::find_if(allDiscoveredNodes.begin(), allDiscoveredNodes.end(), [&](Node node){ return node.thisNodeCoordinate == (*coordinatesToVisit.begin()).first; });
        // auto t_end = std::chrono::high_resolution_clock::now();
        // std::cout << "Finding node took: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

        // t_begin = std::chrono::high_resolution_clock::now();    
        visitNode(nodeToVisit, allDiscoveredNodes, coordinatesToVisit, visitedCoordinates, endPosition, riskLevelMap);
        visitedCoordinates.push_back((*coordinatesToVisit.begin()).first);
        coordinatesToVisit.erase(coordinatesToVisit.begin()); // remove visited coordinate
        std::sort(coordinatesToVisit.begin(), coordinatesToVisit.end(), [](const std::pair<Coordinate, int>& item1, const std::pair<Coordinate, int>& item2){ return item1.second < item2.second; });
        // t_end = std::chrono::high_resolution_clock::now();
        // std::cout << "Visiting node and sorting took: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
    }

    return std::find_if(allDiscoveredNodes.begin(), allDiscoveredNodes.end(), [&](Node node){ return node.thisNodeCoordinate == endPosition; })->localScore;
}

std::vector<std::string> createFullMap(std::vector<std::string> riskLevelMap)
{
    std::vector<std::string> newRiskLevelMap(riskLevelMap.size() * 5, std::string(riskLevelMap[0].size() * 5, 'a'));

    for (int row = 0; row < riskLevelMap.size() * 5; row++)
    {
        for (int column = 0; column < riskLevelMap[0].size() * 5; column++)
        {
            if (column < riskLevelMap[0].size() && row < riskLevelMap.size())
            {
                newRiskLevelMap[row][column] = riskLevelMap[row][column];
            }
            else if (column < riskLevelMap[0].size() && row >= riskLevelMap.size())
            {
                int newVal = (newRiskLevelMap[row - riskLevelMap.size()][column] - '0') + 1;
                newRiskLevelMap[row][column] = (newVal == 10 ? 1 : newVal) + '0';
            }
            else 
            {
                int newVal = (newRiskLevelMap[row][column - riskLevelMap[0].size()] - '0') + 1;
                newRiskLevelMap[row][column] = (newVal == 10 ? 1 : newVal) + '0';
            }
        }
    }
    
    return newRiskLevelMap;
}

int main(void)
{
    std::vector<std::string> testInput = StringOperations::splitString("1163751742\n1381373672\n2136511328\n3694931569\n7463417111\n1319128137\n1359912421\n3125421639\n1293138521\n2311944581", "\n");
    assert(findPathLowestRisk(testInput) == 40);
    
    InputFile inputFile("InputFiles/day15.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 15, puzzle 1: " << std::flush << findPathLowestRisk(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(findPathLowestRisk(createFullMap(testInput)) == 315);
    t_begin = std::chrono::high_resolution_clock::now();    
    std::cout << "Day 15, puzzle 2: " << std::flush << findPathLowestRisk(createFullMap(input)) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
