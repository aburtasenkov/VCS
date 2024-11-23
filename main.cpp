#include "Exception.hpp"
#include "Repository.hpp"

// absolute filepath
const std::filesystem::path CURRENT_PATH{std::filesystem::current_path()};

// filepath in relation to CURRENT_PATH
const std::filesystem::path VCS_PATH{"VCS/"}; 
const std::filesystem::path VCS_COMMITED_STATE{"commited_state/"};
const std::filesystem::path VCS_STAGED_STATE{"staged state/"};
const std::filesystem::path VCS_IGNORE{"ignore"};
const std::filesystem::path VCS_CACHE{"cache"};

// VCS input commands
const std::string INIT = "init";
const std::string ADD = "add";
const std::string COMMIT = "commit";

// magic constants
const int INPUT_COMMAND_INDEX = 1;
const int MIN_INPUT_ARGUMENTS = 2;
const std::string CURRENT_FILENAME = "main.cpp";

void copy_file_to_directory(const std::filesystem::path& source, const std::filesystem::path& copy_directory);
void create_repo_cache(const std::string& repository_name);
Repository* read_cache();
void initialize(const std::string& repository_name);
void add(Repository* repo, const std::filesystem::path& source_path);
void commit(Repository* repo, const std::string& commit_message);

void copy_file_to_directory(const std::filesystem::path& source, const std::filesystem::path& copy_directory)
{
    if (!std::filesystem::exists(source))
        throw Exception{"Missing File Error: File to stage does not exist in directory", {"main.cpp", 64}};
    Document_Namespace::Document doc{source};
    std::ofstream ofs {copy_directory/source};
    if (!ofs.good()) 
        throw Exception{"Reading-Error: could not open file to write", {"main.cpp", 67}};
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
        throw Exception{"Missing File Error: Repository uninitialized", {"main.cpp", 80}};

    Repository* repo = new Repository{};

    return repo;
}

void initialize(const std::string& repository_name)
// initialize a VCS system
{
    // Create VCS directories
    std::filesystem::create_directory(CURRENT_PATH/VCS_PATH);
    std::filesystem::create_directory(CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE);
    std::filesystem::create_directory(CURRENT_PATH/VCS_PATH/VCS_STAGED_STATE);

    // cache for repository data
    if (std::filesystem::exists(CURRENT_PATH/VCS_PATH/VCS_CACHE))
        throw Exception{"Invalid Initialization: Repository already initialized", {"main.cpp", 100}};
    create_repo_cache(repository_name);

    std::ofstream ofs {CURRENT_PATH/VCS_PATH/VCS_IGNORE}; // Create VCS ignore file
}

void add(Repository* repo, const std::filesystem::path& source_path)
// Move file to staged state
{
    copy_file_to_directory(source_path, CURRENT_PATH/VCS_PATH/VCS_STAGED_STATE);
}

void commit(Repository* repo, const std::string& commit_message)
{

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
    if (INPUT_CURRENT_COMMAND == COMMIT)
        commit(repo, argv[INPUT_COMMAND_INDEX + 1]);

    delete repo;

    return 0;
}
catch (Exception& except)
{
    std::cerr << except.what() << std::endl
    << "\t" << except.location().first << ":" << except.location().second << std::endl;
}