#include "stringoperations.hpp"

std::vector<std::string> StringOperations::splitString(std::string stringToSplit, std::string delimiter)
{
    std::vector<std::string> result;
    while(stringToSplit.find(delimiter) != std::string::npos)
    {
        if (stringToSplit.find(delimiter) == 0) 
        {

        stringToSplit = stringToSplit.substr(delimiter.size());
        }
        else
        {
            result.push_back(stringToSplit.substr(0, stringToSplit.find(delimiter)));
            stringToSplit = stringToSplit.substr(stringToSplit.find(delimiter) + delimiter.size());
        }
    }
    result.push_back(stringToSplit);
    return result;
}