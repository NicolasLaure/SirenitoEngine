#include "Utilities/FileReader.h"
#include <fstream>


string FileReader::ParseText(const char* path)
{
	ifstream input;
	input.open(path, ios::in);

	if (!input.good())
	{
		return "Failed";
	}

	string text = "";

	char cursor;
	do
	{
		cursor = input.get();
		if (cursor == EOF)
			continue;

		text += cursor;
	} while (cursor != EOF);

	input.close();

	return text;
}
