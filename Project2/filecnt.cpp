#include <string>
#include <iostream>
#include <filesystem>
#include "version.h"

namespace fs = std::filesystem;

// Prototypes
void explore(int &file, int &folder, double &size, std::string path);

int main(int argc, char *argv[])
{

    int file = 0;
    int folder = 0;
    double size = 0;

    version();

    std::string path = argv[1];
    // std::string path = "/home/peter/testDir";

    if (!fs::exists(path))
        std::cout << path << " doesn't exists!";
    
    else { explore(file, folder, size, path); }

    // Displays the total files, directories, and total size
    std::cout << "The total number of directories in directory <" << path << "> is: " << folder << std::endl;
    std::cout << std::endl;
    std::cout << "The total number of files in directory <" << path << "> is: " << file << std::endl;
    std::cout << std::endl;
    std::cout << "The total number of bytes occupied by all files in directory <" << path << "> is: " << size << std::endl;

  return 0;
}

void explore(int &file, int &folder, double &size, std::string path)
{
    for (const auto & entry : fs::directory_iterator(path))
    {
        
        if (fs::is_directory(entry.path()))
        {
            folder++;
            explore(file, folder, size, entry.path());
        }

        else
        {
            try
            {
                file++;
                size += fs::file_size(entry.path());
            }
            catch(const fs::filesystem_error& e)
            {
                continue;
            }
            
            
        }
        
    }
        
}

