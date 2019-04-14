/*
*  File Name - JSONFileReader.h
*  Project   - Project Horde
*  Module    - FileIO
*  Date      - 04/04/18
*  Author    - Nathan Butt
*  Discription:
*    A JSON File Reader whose contents are read into a JSON Buffer. This can then be read by any
*    object that needs its data.
*
*/

#pragma once

#include <string>
#include <jsoncons\json.hpp>

class JSONFileReader
{
public:
	JSONFileReader() = default;

	void			setFilePath(std::string new_file_path);
	bool			parseFile();
	jsoncons::json&	getFileBuffer();

	jsoncons::json		buffer;

private:
	std::string			file_path = "NULL";
};