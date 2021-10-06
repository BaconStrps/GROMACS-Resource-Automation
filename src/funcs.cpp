#include "funcs.h"

void removeSpaces(std::string& str)
{
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
}