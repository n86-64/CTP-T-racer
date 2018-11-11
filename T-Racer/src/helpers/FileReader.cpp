#include <fstream>
#include "helpers/Utility.h"

#include "FileReader.h"

T_racer_Buffer::T_racer_Buffer(std::string file)
	:filename(file)
{
}

T_racer_Buffer::T_racer_Buffer(uint8_t* contents, size_t size)
	:data(contents),
	dataSize(size)
{
}

void T_racer_Buffer::setFileName(std::string file)
{
	filename = file;
}

bool T_racer_Buffer::readFile()
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

bool T_racer_Buffer::writeFile()
{
	return false;
}

uint8_t T_racer_Buffer::operator[](int seekIndex)
{
	return data[seekIndex];
}

void T_racer_Buffer::extractData(std::string & charBuffer, size_t offset, size_t extractionSize)
{
	charBuffer = std::string((char*)data + offset, extractionSize);
}

void T_racer_Buffer::extractData(std::string& charBuffer, size_t offset)
{
	std::string sData = std::string((char*)data);
	charBuffer = sData.substr(offset, dataSize - offset);
}

void T_racer_Buffer::extractData(std::string & charBuffer, size_t offset, char deliminator)
{
	for (int i = offset; i < dataSize; i++) 
	{
		if (data[i] != deliminator) 
		{
			charBuffer += data[i];
		}
		else 
		{
			break;
		}
	}

}

void T_racer_Buffer::assignBufferData(uint8_t* data, size_t size)
{
	return;
}


