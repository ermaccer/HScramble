// hscramble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>

int main(int argc, char* argv[])
{
	if (argc == 1) {
		std::cout << "HScramble - a tool to scramble or descrable Harvester text files by ermaccer (.idx, .scr)\n"
			<< "Usage: hscramble <file>\n";
		return 1;
	}

	std::ifstream pFile(argv[1], std::ifstream::binary);

	if (!pFile)
	{
		std::cout << "ERROR: Could not open: " << argv[1] << "!" << std::endl;
		return 1;
	}

	if (pFile)
	{
		unsigned int fileSize = std::filesystem::file_size(argv[1]);
		std::unique_ptr<unsigned char[]> dataBuffer = std::make_unique<unsigned char[]>(fileSize);
		pFile.read((char*)dataBuffer.get(), fileSize);

		for (int i = 0; i < fileSize; i++)
		{
			if (dataBuffer[i] == 0x0D || dataBuffer[i] == 0x0A)
				continue;
			// xor
			dataBuffer[i] ^= 0xAA;
		}

		pFile.close();
		std::ofstream oFile(argv[1], std::ofstream::binary);
		oFile.write((char*)dataBuffer.get(), fileSize);

		std::cout << "Finished" << std::endl;
	}
	
}
