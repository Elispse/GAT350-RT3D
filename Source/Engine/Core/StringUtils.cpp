#include "StringUtils.h"

namespace Jackster
{
    std::string ToUpper(std::string input)
    {
        // this function takes the char& from the input string
        // then modifies that specific character in the string to upper
        for (char& c : input) 
        {
            c = std::toupper(c);
        }
        return input;
    }

    std::string ToLower(std::string input)
    {
        // this function takes the char& from the input string
        // then modifies that specific character in the string to lower
        for (char& c : input)
        {
            c = std::tolower(c);
        }
        return input;
    }

    bool IsEqualIgnoreCase(std::string input1, std::string input2)
    {
        bool isEqual = false;
    
        // sets both inputs to lowercase to easily compare
        std::string low1 = ToLower(input1);
        std::string low2 = ToLower(input2);
        // checks if each string now equals eachother
        if (low1 == low2)
        {
            isEqual = true;
        }
        return isEqual;
    }

    std::string CreateUnique(const std::string& str)
    {
        static uint32_t unique = 1;

        return str + std::to_string(unique++);
    }
}
