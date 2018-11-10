/** @file FileReader.h
*  @brief A helper for serializing data.
*
*  A basic buffer object which also contains support for serialising and deserializing data.
*  Allowinf file contents to be loaded. 
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once

#include <string>

class T_racer_Buffer 
{
public:
	T_racer_Buffer() = default;
	T_racer_Buffer(std::string file);
	T_racer_Buffer(uint8_t* contents, size_t size);

	void setFileName(std::string file);
	bool readFile();
	bool writeFile();

	// File Buffer Operators.
	uint8_t operator[](int seekIndex);

	// Read/Write to file buffer. 
	void extractData(std::string& charBuffer, size_t offset, size_t extractionSize);
	void extractData(std::string& charBuffer, size_t offset, size_t& size);
	void assignBufferData(uint8_t* data, size_t size);

	size_t getBufferSize() const { return dataSize; }

private:
	// data in the file.
	uint8_t*		data = nullptr;
	size_t		dataSize = (size_t)0;

private:
	std::string filename = "\0";
};
