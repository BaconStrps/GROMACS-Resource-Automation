#include "defs.h"
#include "LogReader.h"
#include "GmxPotentialReader.h"
int main(int argc, char** argv)
{
	if (strcmp(argv[1], "-log") == 0)
	{
		std::filesystem::path filepath(argv[2]);
		std::filesystem::path folderPath(filepath.parent_path().string() + "/output");
		if (!std::filesystem::exists(folderPath))
		{
			std::filesystem::create_directory(folderPath);
		}
		LogReader log(filepath);

	}

	if (strcmp(argv[1], "-pot") == 0)
	{
		std::filesystem::path filepath(argv[2]);
		std::filesystem::path folderPath = filepath.parent_path().string() + "/output";
		if (!std::filesystem::exists(folderPath))
		{
			std::filesystem::create_directory(folderPath);
		}
		GmxPotentialReader reader(filepath);
	}
}

