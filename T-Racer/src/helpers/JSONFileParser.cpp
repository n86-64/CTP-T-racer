/*
* File Name - JSONFileReader.cpp
* Project   - Project Horde
* Author    - Nathan Butt
*/

#include <fstream>
#include "JSONFileParser.h"

void JSONFileReader::setFilePath(std::string new_file_path)
{
	file_path = new_file_path;
}

bool JSONFileReader::parseFile()
{
	std::ifstream file(file_path);
	bool file_valid = (!file.fail());

	if (file_valid)
	{
		file >> buffer;
		return file_valid;
	}
	else
	{
		std::cout << "T_racer Fatal Error - Scene Manager - Filed to parse scene file."
			<< "\nEither file was not found or file is formatted incorrectly. " << std::endl;
		return file_valid;
	}

}

jsoncons::json& JSONFileReader::getFileBuffer()
{
	return buffer;
}