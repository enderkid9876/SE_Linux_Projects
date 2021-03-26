#include <string>
#include <iostream>
#include <filesystem>
#include "version.h"



int main(int argc, char *argv[])
{

    std::string wholeLine,
                option = argv[argc - 1];
    verison();    

    if (option == "-d")
    {
        getline(std::cin, wholeLine);
        std::cout << wholeLine << std::endl;
    }

    else if (option == "-f")
    {
        getline(std::cin, wholeLine);
        getline(std::cin, wholeLine);
        getline(std::cin, wholeLine);
        std::cout << wholeLine << std::endl;
    }

    else if (option == "-b")
    {
        getline(std::cin, wholeLine);
        getline(std::cin, wholeLine);
        getline(std::cin, wholeLine);
        getline(std::cin, wholeLine);
        getline(std::cin, wholeLine);
        std::cout << wholeLine << std::endl;
    }

    else
        std::cout << "That is not a valid option\n";
    

    return 0;
}
