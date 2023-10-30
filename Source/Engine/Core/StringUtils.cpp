#include "StringUtils.h"
#include <iostream>
#include <cctype>

std::string Jackster::StringUtils::toUpper(std::string input)
{
    // this function takes the char& from the input string
    // then modifies that specific character in the string to upper
    for (char& c : input) 
    {
        c = std::toupper(c);
    }
    return input;
}

std::string Jackster::StringUtils::toLower(std::string input)
{
    // this function takes the char& from the input string
    // then modifies that specific character in the string to lower
    for (char& c : input)
    {
        c = std::tolower(c);
    }
    return input;
}

bool Jackster::StringUtils::IsEqualIgnoreCase(std::string input1, std::string input2)
{
    bool isEqual = false;
    
    // sets both inputs to lowercase to easily compare
    std::string low1 = toLower(input1);
    std::string low2 = toLower(input2);
    // checks if each string now equals eachother
    if (low1 == low2)
    {
        isEqual = true;
    }
    return isEqual;
}

std::string Jackster::StringUtils::CreateUnique(std::string input)
{
    uniNum++;

    std::string result = input + std::to_string(uniNum);

    return result;
}
