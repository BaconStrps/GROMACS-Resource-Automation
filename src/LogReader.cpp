#include "LogReader.h"
#include "funcs.h"
#include "defs.h"

LogReader::LogReader()
{
}

LogReader::LogReader(std::filesystem::path& p)
{
	std::string fn = p.filename().string();
	fn.erase(fn.length() - 4);
	std::string outputPath = p.parent_path().string() + "/output/";
	outputcsv.open(outputPath + fn + "output.csv");

	log.open(p.string());

	if (outputcsv.fail() || log.fail())
	{
		std::cout << "Outputcsv: " << outputcsv.fail();
		std::cout << "\nLog: " << log.fail();
		return;
	}
	read();
}

bool LogReader::Open(std::filesystem::path& p)
{
	std::string fn = p.filename().string();
	fn.erase(fn.length() - 4);
	std::string outputPath = p.parent_path().string() + "/temp";
	outputcsv.open(outputPath + fn + "output.csv");
	log.open(fn);

	read();

	return outputcsv.fail() || log.fail();
}

LogReader::~LogReader()
{
	log.close();
	outputcsv.close();
}

void LogReader::read()
{
	if (log.fail())
		return;


	while (buf.find("Input Parameters:") == std::string::npos) // get to the actual log parameters we want.
	{
		std::getline(log, buf);
	}

	while (buf.length() > 2) // this is what parses the sim parameters
	{
		if (buf.find('(') != std::string::npos)
		{
			while (buf.find('(') != std::string::npos)
				readArray();
			continue;
		}
		else
		{
			if (buf.find('=') != std::string::npos)
				buf.insert(buf.find('=') + 1, ",");
			
			if (buf.find(':') != std::string::npos)
			{
				size_t pos = buf.find(":");
				buf.insert(pos + 1, ",");

				for (size_t i = pos; i+1 < buf.length(); i++)
				{
					if (buf[i] != ' ' && buf[i] != ',' && !isalnum(buf[i+1]) && buf[i] != '\t')
						buf[i + 1] = ',';
				}
			}
			removeSpaces(buf);
		}
		buf.append("\n");
		outputcsv << buf;
		std::getline(log, buf);
	}

	outputcsv << "\n\nEnergies:\n";
	bool end = false;
	while (!log.eof())
	{
		while (buf.find("Step") == std::string::npos && !log.eof())
		{
			std::getline(log, buf);
		}
		readEnergies();
	}



}

void LogReader::readArray()
{
	ArrayParser parser(&log, &buf);
	std::string temp = parser.GetParsedArray();
	outputcsv << temp;
}

void LogReader::readEnergies()
{
	EnergyParser parser(&log, &buf);
	std::vector<std::string> names, values;
	EnergyParams params;
	parser.GetParams(params);



	if (initialized && tables)
	{

		if (params.time == 0 || params.steps == 0)
			return;
		outputcsv << params.time << ',';
		outputcsv << params.steps << ',';
		for (size_t i = 0; i < params.values.size(); i++)
		{
			outputcsv << params.values[i] << ',';
		}
		outputcsv << '\n';
	}
	else if (tables)
	{
		outputcsv << "Time," << "Step,";
		for (size_t i = 0; i < params.names.size(); i++)
		{
			outputcsv << params.names[i] << ',';
		}
		outputcsv << '\n';
		outputcsv << params.time << ',';
		outputcsv << params.steps << ',';
		for (size_t i = 0; i < params.values.size(); i++)
		{
			outputcsv << params.values[i] << ',';
		}
		outputcsv << '\n';
		initialized = true;
	}

	if (!tables)
	{
		outputcsv << "Time: " << params.time << '\n';
		outputcsv << "Step: " << params.steps << '\n';

		for (size_t i = 0; i < params.names.size(); i++)
		{
			outputcsv << params.names[i] << ',' << params.values[i] << '\n';
		}
	}
}
		