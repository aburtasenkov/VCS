#include "Exception.hpp"
#include "Commit.hpp"

// absolute filepath
const std::filesystem::path CURRENT_PATH{std::filesystem::current_path()};

// filepath in relation to CURRENT_PATH
const std::filesystem::path VCS_PATH{"VCS/"}; 
const std::filesystem::path VCS_IGNORE{"ignore"};
const std::filesystem::path VCS_CHANGED_STATE_FILE_PATH{"current_state/"};

// VCS input commands
const std::string INIT = "init";
const std::string ADD = "add";

// magic constants
const int INPUT_COMMAND_INDEX = 1;
const int MIN_INPUT_ARGUMENTS = 2;
const std::string CURRENT_FILENAME = "main.cpp";

std::vector<Commit_Namespace::Commit> commits;

void output_directory_files(std::ostream& os, const std::filesystem::path& directory, const std::string& exception = ".git", const std::string& tabulation = "")
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

void read_from_directory(const std::filesystem::path& source_directory, const std::filesystem::path& copy_directory, const std::string& exception = ".git")
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
                read_from_directory(path, copy_directory/path);
        }
        else
        {
            Document_Namespace::Document file{path.path()};
        }
    }
}

void copy_file_to_directory(const std::filesystem::path& source, const std::filesystem::path& copy_directory)
{
    Document_Namespace::Document doc{source};
    std::ofstream ofs {copy_directory/source};
    if (!ofs.good()) 
        throw Exception{"copy_file_to_directory: could not open file to write", {"main.cpp", 64}};
    ofs << doc;
}

void initialize(const std::string& repository_name)
// initialize a VCS system
{
    // Create VCS directories
    std::filesystem::create_directory(CURRENT_PATH/VCS_PATH);
    std::filesystem::create_directory(CURRENT_PATH/VCS_PATH/VCS_CHANGED_STATE_FILE_PATH);

    std::ofstream ofs {CURRENT_PATH/VCS_PATH/VCS_IGNORE}; // Create VCS ignore file
    output_directory_files(ofs, CURRENT_PATH);
}

void add(const std::filesystem::path& source_path)
{
    if (!std::filesystem::exists(CURRENT_PATH/VCS_PATH/VCS_CHANGED_STATE_FILE_PATH/source_path))
    {
        copy_file_to_directory(source_path, CURRENT_PATH/VCS_PATH/VCS_CHANGED_STATE_FILE_PATH);
        #define modified_path source_path
    }
    else 
        std::filesystem::path modified_path {CURRENT_PATH/VCS_PATH/VCS_CHANGED_STATE_FILE_PATH/source_path};
    Document_Namespace::Document source{source_path};
    Document_Namespace::Document modified{modified_path};
    Commit_Namespace::Filechange changes{source, modified};
    Commit_Namespace::Commit commit{};
    commit.push_back(changes);
    #undef modified_path;
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
    if (INPUT_CURRENT_COMMAND == ADD)
        add(argv[INPUT_COMMAND_INDEX + 1]);

    return 0;
}
catch (Exception& except)
{
    std::cerr << except.what() << std::endl
    << "\t" << except.location().first << ":" << except.location().second << std::endl;
}