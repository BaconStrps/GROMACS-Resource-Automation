#pragma once
#include "defs.h"

struct EnergyParams
{
	std::vector<std::string> names, values;
	uint64_t steps = 0;
	double time = 0;
};

class EnergyParser
{
public:
	EnergyParser(std::ifstream*, std::string*);

	~EnergyParser();

	void GetParams(EnergyParams&);

private:
	void parse();
	std::ifstream* file;
	std::string* buf;
	std::string nameRow;
	std::string valueRow;
	std::vector<std::string> names;
	std::vector<std::string> values;
	double time = -1;
	uint64_t step = -1;
};

