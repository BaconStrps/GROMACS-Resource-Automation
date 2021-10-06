#include "ArrayParser.h"

ArrayParser::ArrayParser() // Empty constructor, make sure to use SetArray if you use this.
{
}

ArrayParser::ArrayParser(std::ifstream* _file, std::string* currentline) // Explicit constructor
{
	arrayData = currentline;
	file = _file;
	parse();
}

ArrayParser::~ArrayParser()
{

}

void ArrayParser::SetArray(std::ifstream* _file, std::string* currentline)
{
	arrayData = currentline;
	file = _file;
	parse();
}

std::string& ArrayParser::GetParsedArray()
{
	return dataList;
}

void ArrayParser::parse()
{

	arrayName = arrayData->substr(0, arrayData->find('('));

	const char* p_Data = &arrayData->at(arrayData->find('(') + 1);
	int mult1, mult2;

	if (isdigit(*p_Data))
		mult1 = atoi(p_Data);
	else
		throw std::runtime_error("Failed to find array length");

	p_Data += 2;
	if (isdigit(*p_Data))
		mult2 = atoi(p_Data);
	else
		mult2 = 1; // single dimensional array

	arraySize = mult1 * mult2;
	lines = mult1;
	dataLength = mult2;

	lineLength = 12 * dataLength + (dataLength - 1)*2;

	if (dataLength > 1)
	{
		parseMultiDimensional();
	}
	else
	{
		parseSingleDimensional();
	}

}

void ArrayParser::parseMultiDimensional()
{
	std::getline(*file, *arrayData);
	size_t dataStart = arrayData->find("{") + 1;
	for (size_t i = 0; i < lines; i++)
	{
		dataList.append(arrayName + "[" + std::to_string(i) + "] =,");
		dataList.append(arrayData->substr(dataStart, lineLength) + '\n');

		std::getline(*file, *arrayData);
	}

	file->seekg(-file->gcount(), file->cur);
}

void ArrayParser::parseSingleDimensional()
{
	std::getline(*file, *arrayData);
	size_t currentpos = arrayData->find('=') + 1;

	for (size_t i = 0; i < lines; i++)
	{
		dataList.append(arrayName + "[" + std::to_string(i) + "] =,");
		dataList.append(arrayData->substr(currentpos, lineLength) + '\n');
		std::getline(*file, *arrayData);
	}

	file->seekg(-file->gcount(), file->cur);
}
