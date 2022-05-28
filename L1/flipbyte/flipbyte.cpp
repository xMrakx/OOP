#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string input_string;
};

std::optional<Args> Parse_Args(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Usage: flipbyte.exe <input number>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.input_string = argv[1];
	return args;
}

bool Input_Chek(std::string input_string)
{
	for (int count = 0; count < size(input_string); count++)
	{
		if (!(input_string[count] >= '0' && input_string[count] <= '9'))
		{
			if (!(input_string[count] == '-' && count == 0))
			{
				std::cout << "Input argument is not a number" << std::endl;
				return 1;
			}
		}
	}
	return 0;
}

bool Number_Check(int number)
{
	if (!(number >= 0 && number <= 255))
	{
		std::cout << "Input number out of 0 - 255 range" << std::endl;
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	auto input_string = Parse_Args(argc, argv);
	if (!input_string)
	{
		return 1;
	}

	if (Input_Chek(input_string->input_string))
	{
		return 1;
	}

	int input_number = stoi(input_string->input_string);
	if (Number_Check(input_number))
	{
		return 1;
	}

	int one = 1;
	int number = 0;
	int out_number = 0;
	for (int count = 0; count < 8; count++)
	{
		number = input_number & one;
		out_number = out_number ^ number;
		input_number = input_number >> 1;
		if (count != 7)
		{
			out_number = out_number << 1;
		}
	}
	std::cout << out_number << std::endl;
}

