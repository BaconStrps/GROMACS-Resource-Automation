#include "GmxPotentialReader.h"
#include "funcs.h"

GmxPotentialReader::GmxPotentialReader(std::filesystem::path& p)
{
	file.open(p);

	std::filesystem::path outputpath = p;
	std::string filename = p.stem().string();
	filename.append("output.csv");

	outputpath.replace_filename("output/" + filename);

	outputcsv.open(outputpath, std::ios_base::trunc);

	read();
}

GmxPotentialReader::~GmxPotentialReader()
{
	outputcsv.close();
	file.close();
}

void GmxPotentialReader::read()
{
	getline(file, buf);
	while (	buf.find("#") != std::string::npos || 
			buf.find("@") != std::string::npos)
	{
		getline(file, buf);
	}

	bool alnum = false;
	while (!file.eof())
	{
		for (char& c : buf)
		{
			if (alnum && isspace(c))
			{
				c = ',';
				alnum = false;
			}
			else if (isalnum(c))
			{
				alnum = true;
			}
		}

		removeSpaces(buf);

		outputcsv << buf << '\n';

		getline(file, buf);

		alnum = false;
	}
}
