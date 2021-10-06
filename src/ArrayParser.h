#pragma once
#include "defs.h"
class ArrayParser
{
public:
	ArrayParser();
	ArrayParser(std::ifstream*, std::string*);

	~ArrayParser();

	void SetArray(std::ifstream*, std::string*);

	std::string& GetParsedArray();

private:
	void parse();

	void parseMultiDimensional();
	void parseSingleDimensional();


	std::string* arrayData = nullptr;
	std::ifstream* file = nullptr;
	std::string dataList;
	std::string arrayName;
	size_t arraySize = 0;
	size_t lines = 0;
	size_t dataLength = 0;
	size_t lineLength = 0;
};

