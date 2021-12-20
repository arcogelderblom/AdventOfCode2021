#include <iostream>
#include <chrono>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"

int main(void)
{
    std::cout << "Hello world!" << std::endl;
    // std::vector<std::string> testInput = StringOperations::splitString("[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]\n[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]\n[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]\n[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]\n[7,[5,[[3,8],[1,4]]]]\n[[2,[2,2]],[8,[8,1]]]\n[2,9]\n[1,[[[9,3],9],[[9,0],[0,7]]]]\n[[[5,[7,4]],7],1]\n[[[[4,2],2],6],[8,7]]", "\n");
    // std::vector<std::string> testInput2 = StringOperations::splitString("[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]\n[[[5,[2,8]],4],[5,[[9,9],0]]]\n[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]\n[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]\n[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]\n[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]\n[[[[5,4],[7,7]],8],[[8,3],8]]\n[[9,3],[[9,9],[6,[4,9]]]]\n[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]\n[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]", "\n");
    // assert(getMagnitude(testInput) == 3488);
    // assert(getMagnitude(testInput2) == 4140);
    
    // InputFile inputFile("InputFiles/day19.txt");
    // std::vector<std::string> input = inputFile.getContentAsString("\n");
    // auto t_begin = std::chrono::high_resolution_clock::now();
    // std::cout << "Day 19, puzzle 1: " << getMagnitude(input) << std::endl;
    // auto t_end = std::chrono::high_resolution_clock::now();
    // std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    // assert(getLargestPossibleMagnitude(testInput2) == 3993);    
    // t_begin = std::chrono::high_resolution_clock::now();    
    // std::cout << "Day 19, puzzle 2: " << getLargestPossibleMagnitude(input) << std::endl;
    // t_end = std::chrono::high_resolution_clock::now();
    // std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
