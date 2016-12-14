## Example

```c++
#include <iostream>
#include <string>
#include "wavDecoder.h"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;



int main(int argc, char* argv[])
{
	const char* filePath;
	string input;
	if (argc <= 1)
	{
		cout << "Input wave file name: ";
		cin >> input;
		cin.get();
		filePath = input.c_str();
	}
	else
	{
		filePath = argv[1];
		cout << "Input wave file name: " << filePath << endl;
	}
	wavDecoder wav(filePath);
	if (wav.getError() != 0)
	{
		return 0;
	}

	auto wavHeader=wav.getHeader();
	cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
	cout << "WAVE header                :" << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
	cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
	cout << "Data size                  :" << wavHeader.ChunkSize << endl;

	// Display the sampling Rate from the header
	cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << endl;
	cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
	cout << "Number of channels         :" << wavHeader.NumOfChan << endl;
	cout << "Number of bytes per second :" << wavHeader.bytesPerSec << endl;
	cout << "Data length                :" << wavHeader.Subchunk2Size << endl;
	cout << "Audio Format               :" << wavHeader.AudioFormat << endl;
	// Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

	cout << "Block align                :" << wavHeader.blockAlign << endl;
	cout << "Data string                :" << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;
	return 0;
}

```