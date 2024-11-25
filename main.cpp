#include "Exception.hpp"
#include "Repository.hpp"

// absolute filepath
const std::filesystem::path CURRENT_PATH{std::filesystem::current_path()};

// filepath in relation to CURRENT_PATH
const std::filesystem::path VCS_PATH{"VCS/"}; 
const std::filesystem::path VCS_COMMITED_STATE{"commited state/"};
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

void copy_file_to_directory(const std::filesystem::path& source, const std::filesystem::path& copy_directory)
{
    if (!std::filesystem::exists(source))
        throw Exception{"Missing File Error: File to stage does not exist in directory", CURRENT_FILENAME};
    std::filesystem::copy(source, copy_directory);
}

Repository* read_cache()
{
    if (!std::filesystem::exists(CURRENT_PATH/VCS_PATH/VCS_CACHE))
        throw Exception{"Missing File Error: Repository uninitialized", CURRENT_FILENAME};

    std::ifstream ifs{CURRENT_PATH/VCS_PATH/VCS_CACHE};

    Repository* repo = new Repository{};

    ifs >> (*repo);

    ifs.close();

    return repo;
}

void save_cache(Repository* repo)
{
    std::ofstream ofs{CURRENT_PATH/VCS_PATH/VCS_CACHE};
    ofs << (*repo);
    ofs.close();
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
        throw Exception{"Invalid Initialization: Repository already initialized", CURRENT_FILENAME};
    Repository repo{repository_name};
    save_cache(&repo);

    std::ofstream ofs {CURRENT_PATH/VCS_PATH/VCS_IGNORE}; // Create VCS ignore file
    ofs.close();
}

void add(const std::filesystem::path& source_path)
// Move file to staged state
{
    copy_file_to_directory(source_path, CURRENT_PATH/VCS_PATH/VCS_STAGED_STATE);
}

bool already_commited(const std::filesystem::path& filepath)
// returns true if both there are any files in commited state that have the same filename
{
    for (auto& commited_filepath : std::filesystem::directory_iterator{CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE})
    {
        if (commited_filepath.path().filename() == filepath.filename())
            return true;
    }
    return false;
}

void commit(Repository* repo, const std::string& commit_message)
{
    Commit_Namespace::Commit commit{};
    for (auto& filepath_iterator : std::filesystem::directory_iterator{CURRENT_PATH/VCS_PATH/VCS_STAGED_STATE})
    {
        if (!already_commited(filepath_iterator.path()))
        {
            copy_file_to_directory(filepath_iterator.path(), CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE);
            return;
        }

        std::filesystem::path commited_filepath{filepath_iterator.path().filename()};

        Commit_Namespace::Filechange fc{
                                        Document_Namespace::Document{CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE/commited_filepath},
                                        Document_Namespace::Document{filepath_iterator.path()}
                                        };

        if (fc.changes.is_modified())
        {
            commit.push_back(fc);
        }
    }
    repo->add_commit(commit);

    if (!std::filesystem::exists(CURRENT_PATH/VCS_PATH/VCS_CACHE))
        throw Exception{"Missing File Error: Repository uninitialized", CURRENT_FILENAME};
    save_cache(repo);
}

int main(int argc, char** argv)
try
{    
    // argv should at least contain a string after executable name
    if (argc < MIN_INPUT_ARGUMENTS)
        throw Exception{"Syntax-Error: Bad Command Line Input", CURRENT_FILENAME};

    std::string INPUT_CURRENT_COMMAND = argv[INPUT_COMMAND_INDEX];

    if (INPUT_CURRENT_COMMAND == INIT)
        initialize(argv[INPUT_COMMAND_INDEX + 1]);
    else 
    {    
        Repository* repo = read_cache();

        if (INPUT_CURRENT_COMMAND == ADD)
            add(argv[INPUT_COMMAND_INDEX + 1]);
        if (INPUT_CURRENT_COMMAND == COMMIT)
            commit(repo, argv[INPUT_COMMAND_INDEX + 1]);

        delete repo;
    }

    return 0;
}
catch (Exception& except)
{
    std::cerr << except.what() << std::endl
    << "\t" << except.where() << std::endl;
    return 1;
}