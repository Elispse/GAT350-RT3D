#pragma once
#include <string>

namespace Jackster
{
	class StringUtils
	{
	public:
		// function returns string input to uppercase
		std::string toUpper(std::string input);
		// function returns string input to lowercase
		std::string toLower(std::string input);
		// function compares two strings and returns if they equal eachother
		bool IsEqualIgnoreCase(std::string input1, std::string input2);
		// function takes a string as input and appends a static unsigned integer to it. 
		// The integer should increment with each call, ensuring a unique string each time.
		std::string CreateUnique(std::string input);
	private:
		unsigned int uniNum = 0;
	};
}