#include <fstream>
#include "helpers/Utility.h"

#include "FileReader.h"

T_racer_FileBuffer::T_racer_FileBuffer(std::string file)
	:filename(file)
{
}

void T_racer_FileBuffer::setFileName(std::string file)
{
	filename = file;
}

bool T_racer_FileBuffer::readFile()
{
	std::fstream  fileStream;
	fileStream.open(filename.c_str(), std::ios::in | std::ios::binary);


	if (fileStream.fail()) 
	{
		return false;
	}

	fileStream.seekg(0, fileStream.end);
	dataSize = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);

	T_RACER_RELEASE_BUFFER((void*&)data);

	data = new uint8_t[dataSize];
	fileStream.read((char*)data, dataSize);

	return true;
}

bool T_racer_FileBuffer::writeFile()
{
	return false;
}

uint8_t T_racer_FileBuffer::operator[](int seekIndex)
{
	return data[seekIndex];
}

void T_racer_FileBuffer::extractData(std::string & charBuffer, size_t offset, size_t extractionSize)
{
	charBuffer = std::string((char*)data + offset, extractionSize);
}

void T_racer_FileBuffer::assignBufferData(uint8_t* data, size_t size)
{
	return;
}


