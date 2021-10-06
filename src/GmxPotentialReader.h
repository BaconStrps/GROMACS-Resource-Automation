#pragma once
#include "defs.h"
class GmxPotentialReader
{
public:
	GmxPotentialReader(std::filesystem::path&);

	~GmxPotentialReader();

private:

	void read();

	std::ofstream outputcsv;
	std::ifstream file;
	std::string buf;

};

