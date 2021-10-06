#include "EnergyParser.h"
#include "funcs.h"

EnergyParser::EnergyParser(std::ifstream* _file, std::string* _buf) // assumes both pointers point to valid objects
{
	file = _file;
	buf = _buf;
	parse();
}

EnergyParser::~EnergyParser()
{
}

void EnergyParser::GetParams(EnergyParams& params)
{
	if (names.empty() || values.empty())
		return;
	params.names = names;
	params.values = values;
	params.steps = step;
	params.time = time;
}

void EnergyParser::parse()
{
	std::getline(*file, *buf);
	size_t curpos = 0;

	for (size_t i = 0; i < buf->length(); i++)
	{
		if (isdigit(buf->at(i)) && step == -1)
		{
			step = atoi(&buf->at(i));
			if (step != 0)
				i += static_cast<size_t>(log10(step));
			else
				i++;
		}
		else if (isdigit(buf->at(i)) && time == -1)
		{
			time = atof(&buf->at(i));
			break;
		}
	}

	while (buf->find("Energies") == std::string::npos && !file->eof())
	{
		std::getline(*file, *buf);
	}

	std::getline(*file, nameRow);
	std::getline(*file, valueRow);

	while (nameRow.length() > 1 && valueRow.length() > 1)
	{
		for (size_t i = 0; i < nameRow.length() / 15; i++)
		{
			names.push_back(nameRow.substr(curpos, 15));
			values.push_back(valueRow.substr(curpos, 15));

			curpos += 15;
		}
		curpos = 0;

		std::getline(*file, nameRow);
		std::getline(*file, valueRow);
	}
	
		for (std::string& str : names)
			removeSpaces(str);
		for (std::string& str : values)
			removeSpaces(str);
}
