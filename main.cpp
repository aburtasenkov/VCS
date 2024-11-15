#include <iostream>
#include <fstream>
#include <filesystem>
#include "Exception.hpp"
#include "Document/Document.hpp"

const std::string CURRENT_FILENAME = "main.cpp";

const std::filesystem::path CURRENT_PATH{"/home/aburtasenkov/Pet-Projects/VCS"};
const std::filesystem::path VCS_PATH{"VCS"}; 
const std::filesystem::path VCS_IGNORE_PATH{VCS_PATH/"ignore"};

const std::string INIT = "init";

const int INPUT_COMMAND_INDEX = 1;
const int MIN_INPUT_ARGUMENTS = 2;

void directory_files_output(std::ostream& os, std::filesystem::path directory, std::string tabulation = "")
// Output all files
// If dir is directory call output_directory on it with extra "    " tabulation for visibility
{
    for (const auto& dir : std::filesystem::directory_iterator{directory})
    {
        if (dir.is_directory())
            directory_files_output(os, dir, tabulation + "    ");
        else
            os << tabulation << dir << std::endl;
    }
}

void initialize(std::string repository_name)
{
    std::ofstream ofs {VCS_IGNORE_PATH};
    
    directory_files_output(ofs, CURRENT_PATH);
}

int main(int argc, char** argv)
try
{    
    // argv should at least contain a string after executable name
    if (argc < MIN_INPUT_ARGUMENTS)
        throw Exception{"Syntax-Error: Bad Command Line Input", {CURRENT_FILENAME, 15}};

    std::string INPUT_CURRENT_COMMAND = argv[INPUT_COMMAND_INDEX];

    if (INPUT_CURRENT_COMMAND == INIT)
        initialize(argv[INPUT_COMMAND_INDEX + 1]);

    return 0;
}
catch (Exception& except)
{
    std::cerr << except.what() << std::endl
    << "\t" << except.location().first << ":" << except.location().second << std::endl;
}