#include "Exception.hpp"
#include "Repository.hpp"

// absolute filepath
const std::filesystem::path CURRENT_PATH{std::filesystem::current_path()};

// filepath in relation to CURRENT_PATH
const std::filesystem::path VCS_PATH{"VCS/"}; 
const std::filesystem::path VCS_CHANGED_STATE_FILE_PATH{"current_state/"};
const std::filesystem::path VCS_IGNORE{"ignore"};
const std::filesystem::path VCS_CACHE{"cache"};

// VCS input commands
const std::string INIT = "init";
const std::string ADD = "add";

// magic constants
const int INPUT_COMMAND_INDEX = 1;
const int MIN_INPUT_ARGUMENTS = 2;
const std::string CURRENT_FILENAME = "main.cpp";

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
        throw Exception{"Reading-Error: could not open file to write", {"main.cpp", 64}};
    ofs << doc;
}

void create_repo_cache(const std::string& repository_name)
// initialize cache files for a repository
{
    std::ofstream ofs{CURRENT_PATH/VCS_PATH/VCS_CACHE};
    ofs << repository_name << "\n";
}

Repository* read_cache()
{
    if (!std::filesystem::exists(CURRENT_PATH/VCS_PATH/VCS_CACHE))
        throw Exception{"Missing File Error: Repository uninitialized", {"main.cpp", 79}};

    Repository* repo = new Repository{};

    return repo;
}

void initialize(const std::string& repository_name)
// initialize a VCS system
{
    // Create VCS directories
    std::filesystem::create_directory(CURRENT_PATH/VCS_PATH);
    std::filesystem::create_directory(CURRENT_PATH/VCS_PATH/VCS_CHANGED_STATE_FILE_PATH);

    // cache for repository data
    if (std::filesystem::exists(CURRENT_PATH/VCS_PATH/VCS_CACHE))
        throw Exception{"Invalid Initialization: Repository already initialized", {"main.cpp", 100}};
    create_repo_cache(repository_name);

    std::ofstream ofs {CURRENT_PATH/VCS_PATH/VCS_IGNORE}; // Create VCS ignore file
    output_directory_files(ofs, CURRENT_PATH);
}

void add(Repository* repo, const std::filesystem::path& source_path)
// add file to next commit
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
    #undef modified_path
    Commit_Namespace::Filechange changes{source, modified};
    Commit_Namespace::Commit commit{};
    commit.push_back(changes); 
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

    Repository* repo = read_cache();

    if (INPUT_CURRENT_COMMAND == ADD)
        add(repo, argv[INPUT_COMMAND_INDEX + 1]);

    delete repo;

    return 0;
}
catch (Exception& except)
{
    std::cerr << except.what() << std::endl
    << "\t" << except.location().first << ":" << except.location().second << std::endl;
}