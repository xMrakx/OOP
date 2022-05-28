#include "Decode.h"
#include <iostream>
#include <string>

int main()
{
    std::string line;
    getline(std::cin, line);
    std::cout << HtmlDecode(line) << std::endl;
}

