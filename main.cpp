#include <iostream>
#include <fstream>
#include <filesystem>
#include "Exception.hpp"
#include "DocumentComparison.hpp"

// absolute filepath
const std::filesystem::path CURRENT_PATH{std::filesystem::current_path()};

// filepath in relation to CURRENT_PATH
const std::filesystem::path VCS_PATH{"VCS/"}; 
const std::filesystem::path VCS_IGNORE{"ignore"};
const std::filesystem::path VCS_FILE_COPY_PATH{"files/"};

// VCS input commands
const std::string INIT = "init";

// magic constants
const int INPUT_COMMAND_INDEX = 1;
const int MIN_INPUT_ARGUMENTS = 2;
const std::string CURRENT_FILENAME = "main.cpp";

void output_directory_files(std::ostream& os, std::filesystem::path directory, std::string exception = ".git", std::string tabulation = "")
// Output all files to os
// If variable directory is a directory call output_directory on it with extra "    " tabulation for visibility
// Pre-Condition: directory exists in PC memory
{
    for (const auto& path : std::filesystem::directory_iterator{directory})
    {
        if (path.is_directory())
        {
            if (!(path.path() == directory/exception))
                output_directory_files(os, path, exception, tabulation + "    ");
        }
        else
            os << tabulation << path << std::endl;
    }
}

void copy_files_to_directory(std::filesystem::path source_directory, std::filesystem::path copy_directory, std::string exception = ".git")
// Copy each file from source_directory to copy_directory
// Pre-Condition: copy_directory exists in PC memory
{
    // iterate through each file in source_directory
    for (const auto& path : std::filesystem::directory_iterator{source_directory})
    {
        // if the path is a directory - copy the directory to copy_directory
        if (path.is_directory())
        {
            if (!(path.path() == source_directory/exception))
                copy_files_to_directory(path, copy_directory/path);
        }
        else
        {
            DocumentClass::Document file{path.path()};  // path.path() returns std::filesystem::path
        }
    }
}

void initialize(std::string repository_name)
{
    // Create VCS directories
    std::filesystem::create_directory(CURRENT_PATH/VCS_PATH);
    std::filesystem::create_directory(CURRENT_PATH/VCS_PATH/VCS_FILE_COPY_PATH);

    std::ofstream ofs {CURRENT_PATH/VCS_PATH/VCS_IGNORE}; // Create VCS ignore file
    output_directory_files(ofs, CURRENT_PATH);

    copy_files_to_directory(CURRENT_PATH, CURRENT_PATH/VCS_PATH/VCS_FILE_COPY_PATH);
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