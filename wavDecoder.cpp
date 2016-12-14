/*
 *	from http://stackoverflow.com/questions/13660777/c-reading-the-data-part-of-a-wav-file
 */
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include "wavDecoder.h"

using namespace std;

// find the file size
inline int getFileSize(FILE* inFile)
{
	int fileSize = 0;
	fseek(inFile, 0, SEEK_END);

	fileSize = ftell(inFile);

	fseek(inFile, 0, SEEK_SET);
	return fileSize;
}

wavDecoder::~wavDecoder()
{
	delete[] soundData;
	soundData = nullptr;
}

wavDecoder::wavDecoder(std::string path)
{
	long remainSize;
	ifstream in("./sound.wav", ios::in | ios::binary | ios::ate);
	if (in.is_open() == false)
	{
		error = -1;
		return;
	}
	remainSize = in.tellg();
	if (remainSize <= sizeof(header))
	{
		error = -2;
		return;
	}
	in.seekg(0, ios::beg);
	in.read(reinterpret_cast<char *>(&header), sizeof(header));

	remainSize -= sizeof(header);
	if (remainSize != header.Subchunk2Size)
	{
		error = -3;
		return;
	}
	soundDataSize = header.Subchunk2Size;
	soundData = new char[remainSize];
	in.read(soundData, remainSize);
	in.close();
}