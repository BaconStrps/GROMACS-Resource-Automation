#pragma once
#include "ArrayParser.h"
#include "EnergyParser.h"
#include <iostream>
#include <string>
#include <fstream>
class LogReader
{
public:
	LogReader();
	LogReader(std::filesystem::path&);
	bool Open(std::filesystem::path&);
	~LogReader();

private:

	void read();
	void readArray();
	void readEnergies();

	std::ofstream outputcsv;
	std::ifstream log;
	std::string buf;

	const bool tables = true;
	bool initialized = false;
};

