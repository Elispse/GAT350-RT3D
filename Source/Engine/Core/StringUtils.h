#pragma once
#include <string>

namespace Jackster
{
	class StringUtils
	{
	public:
		// function returns string input to uppercase
		static std::string toUpper(std::string input);
		// function returns string input to lowercase
		static std::string toLower(std::string input);
		// function compares two strings and returns if they equal eachother
		static bool IsEqualIgnoreCase(std::string input1, std::string input2);
		// function takes a string as input and appends a static unsigned integer to it. 
		// The integer should increment with each call, ensuring a unique string each time.
		static std::string CreateUnique(const std::string& str);
	private:
		unsigned int uniNum = 0;
	};
}