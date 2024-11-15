#include <iostream>
#include <fstream>
#include <filesystem>
#include "Exception.hpp"
#include "Document/Document.hpp"

const std::string CURRENT_FILENAME = "main.cpp";

const std::filesystem::path CURRENT_PATH{"/home/aburtasenkov/Pet-Projects/git"};
const std::filesystem::path VCS_PATH{"VCS"}; 
const std::filesystem::path VCS_IGNORE_PATH{VCS_PATH/"ignore"};

const std::string INIT = "init";

const int COMMAND_INDEX = 1;

void output_to_directory(std::ostream& os, std::filesystem::path directory, std::string tabulation = "")
// Output all files
// If dir is directory call output_directory on it with extra "    " tabulation for visibility
{
    for (const auto& dir : std::filesystem::directory_iterator{directory})
    {
        if (dir.is_directory())
            output_to_directory(os, dir, tabulation + "    ");
        else
            os << tabulation << dir << std::endl;
    }
}

void initialize(std::string repository_name)
{
    std::ofstream ofs {VCS_IGNORE_PATH};
    
    output_to_directory(ofs, CURRENT_PATH);
}

int main(int argc, char** argv)
try
{    
    // argv should at least contain a string after executable name
    if (argc < 2)
        throw Exception{"Syntax-Error: Bad Command Line Input", {CURRENT_FILENAME, 15}};

    std::string CURRENT_COMMAND = argv[COMMAND_INDEX];

    if (CURRENT_COMMAND == INIT)
        initialize(argv[COMMAND_INDEX + 1]);

    return 0;
}
catch (Exception& except)
{
    std::cerr << except.what() << std::endl
    << "\t" << except.location().first << ":" << except.location().second << std::endl;
}