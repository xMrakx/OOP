#include <iostream>
#include <optional>
#include <string>
#include <fstream>

enum class WorkMode
{
	crypt, decrypt
};

struct Args
{
	WorkMode workMode;
	std::string inputFileName;
	std::string outputFileName;
	int key;
};

WorkMode DefineWorkMode(const std::string& workMode)
{
	if (workMode == "crypt")
	{
		return WorkMode::crypt;
	}
	else if (workMode == "decrypt")
	{
		return WorkMode::decrypt;
	}
	else
	{
		throw std::invalid_argument("Invalid work mode");
	}
}

int KeyToInt(const std::string& key)
{
	int keyInt;
	try
	{
		keyInt = std::stoi(key);
	}
	catch (std::invalid_argument error)
	{
		std::cout << "Invalid crypt key" << std::endl;
		return NULL;
	}

	if (keyInt < 0 || keyInt > 255)
	{
		std::cout << "Key should be a number, range of 0 to 255" << std::endl;
		return NULL;
	}
	return keyInt;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Usage: crypt.exe <mode> <input file> <output file> <key>" << std::endl;
		return std::nullopt;
	}

	Args args;
	try
	{
		args.workMode = DefineWorkMode(argv[1]);
	}
	catch(std::invalid_argument error)
	{
		std::cout << "Invalid work mode" << std::endl;
		std::cout << "It should be 'crypt' or 'decrypt'" << std::endl;
		return std::nullopt;
	}

	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.key = KeyToInt(argv[4]);
	if (!args.key)
	{
		return std::nullopt;
	}

	return args;
}

char MixByteCrypt(unsigned char inputChar)
{
	unsigned char mixedChar = 0;
	unsigned char tempChar = 0;
	
	tempChar = inputChar & 0b00000111;
	tempChar <<= 2;
	mixedChar ^= tempChar;
	tempChar = inputChar & 0b00011000;
	tempChar <<= 3;
	mixedChar ^= tempChar;
	tempChar = inputChar & 0b01100000;
	tempChar >>= 5;
	mixedChar ^= tempChar;
	tempChar = inputChar & 0b10000000;
	tempChar >>= 2;
	mixedChar ^= tempChar;
	return mixedChar;
}

int CryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key) 
{
	char inputChar;
	while (inputFile.get(inputChar))
	{
		inputChar ^= key;
		inputChar = MixByteCrypt(inputChar);
		outputFile << inputChar;
	}
	return 0;
}

char MixByteDecrypt(unsigned char inputChar)
{
	unsigned char mixedChar = 0;
	unsigned char tempChar = 0;

	tempChar = inputChar & 0b00000011;
	tempChar <<= 5;
	mixedChar ^= tempChar;
	tempChar = inputChar & 0b00011100;
	tempChar >>= 2;
	mixedChar ^= tempChar;
	tempChar = inputChar & 0b00100000;
	tempChar <<= 2;
	mixedChar ^= tempChar;
	tempChar = inputChar & 0b11000000;
	tempChar >>= 3;
	mixedChar ^= tempChar;
	return mixedChar;
}

int DecryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key)
{
	char inputChar;
	while (inputFile.get(inputChar))
	{
		inputChar = MixByteDecrypt(inputChar);
		inputChar ^= key;
		outputFile << inputChar;
	}
	return 0;
}

bool WorkWithFiles(const std::optional<Args>& args)
{
	std::ifstream inputFile;
	inputFile.open(args->inputFileName, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << args->inputFileName << " for reading" << std::endl;
		return false;
	}
	std::ofstream outputFile;
	outputFile.open(args->outputFileName, std::ios::binary);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open " << args->outputFileName << " for writing" << std::endl;
		return false;
	}

	switch (args->workMode)
	{
	case WorkMode::crypt:
		CryptFile(inputFile, outputFile, args->key);
		break;
	case WorkMode::decrypt:
		DecryptFile(inputFile, outputFile, args->key);
		break;
	}

}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	if (!WorkWithFiles(args))
	{
		return 1;
	}
	
	return 0;
}