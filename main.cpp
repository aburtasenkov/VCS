#include "Exception.hpp"
#include "Repository.hpp"

// absolute filepath
const std::filesystem::path CURRENT_PATH{std::filesystem::current_path()};

// filepath in relation to CURRENT_PATH
const std::filesystem::path VCS_PATH{"VCS/"}; 
const std::filesystem::path VCS_COMMITED_STATE{"commited_state/"};
const std::filesystem::path VCS_STAGED_STATE{"staged_state/"};
const std::filesystem::path VCS_IGNORE{"ignore"};
const std::filesystem::path VCS_CACHE{"cache"};
const std::filesystem::path VCS_COMMIT_DATA{"commit_data"};

// VCS input commands
const std::string INIT = "init";
const std::string ADD = "add";
const std::string COMMIT = "commit";
const std::string RESTORE = "restore";

// magic constants
const int INPUT_COMMAND_INDEX = 1;
const int MIN_INPUT_ARGUMENTS = 3;
const std::string CURRENT_FILENAME = "main.cpp";

void copy_file_to_directory(const std::filesystem::path& source, const std::filesystem::path& copy_directory)
// copy source to copy_directory
{
    if (!std::filesystem::exists(source))
        throw Exception{"Missing File Error: File to stage does not exist in directory", CURRENT_FILENAME};
    std::filesystem::copy(source, copy_directory);
}

Repository* read_cache()
// load data into Repository object
// return object containing loaded data
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
// save data from Repository object
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

    // create commit_data file
    std::ofstream vcs_commit_data{CURRENT_PATH/VCS_PATH/VCS_COMMIT_DATA};
    std::ofstream vcs_ignore {CURRENT_PATH/VCS_PATH/VCS_IGNORE};
    vcs_ignore.close();
    vcs_commit_data.close();
}

void add(const std::filesystem::path& source_path)
// Move file to staged state
{
    copy_file_to_directory(source_path, CURRENT_PATH/VCS_PATH/VCS_STAGED_STATE);
}

bool already_commited(const std::filesystem::path& filepath)
// returns true if both there are any files in commited state that have the same filename
{
    for (auto& commited_state : std::filesystem::directory_iterator{CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE})
    {
        if (commited_state.path().filename() == filepath.filename())
            return true;
    }
    return false;
}

void remove_files_from_directory(const std::filesystem::path dir)
// delete all files from a directory
{
    for (auto iterator : std::filesystem::directory_iterator{dir})
    {    
        if(!std::filesystem::remove(iterator.path()))
            throw Exception{"Delete Error: could not remove all files from directory " / dir, CURRENT_FILENAME};
    }
}

void remove_file_from_directory(const std::filesystem::path path)
{  
    if(!std::filesystem::remove(path))
        throw Exception{"Delete Error: could not remove file from directory " / path, CURRENT_FILENAME};
}

void commit(Repository* repo, const std::string& commit_message)
// make a commit to Repository object with commit_message
{
    if (!std::filesystem::exists(CURRENT_PATH/VCS_PATH/VCS_CACHE))
        throw Exception{"Missing File Error: Repository uninitialized", CURRENT_FILENAME};
    Commit_Namespace::Commit commit{commit_message};
    std::filesystem::path filename;

    // iterate through each file in staged state
    for (auto& filepath_iterator : std::filesystem::directory_iterator{CURRENT_PATH/VCS_PATH/VCS_STAGED_STATE})
    {
        // if not already commited copy to commited state in order to generalize function
        // e.g handle copy of a function as source state with no changes to modified state
        if (!already_commited(filepath_iterator.path()))
        {
            copy_file_to_directory(filepath_iterator.path(), CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE);
        }

        filename = filepath_iterator.path().filename();

        // commited state as source, staged state as modified
        Commit_Namespace::Filechange fc{
                                        Document_Namespace::Document{CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE/filename},
                                        Document_Namespace::Document{CURRENT_PATH/VCS_PATH/VCS_STAGED_STATE/filename}
                                        };

        commit.push_back(fc);

        remove_file_from_directory(CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE/filename);
        copy_file_to_directory(CURRENT_PATH/VCS_PATH/VCS_STAGED_STATE/filename, CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE);
    }
    repo->add_commit(commit);

    save_cache(repo);

    // clear staged state for future commits
    remove_files_from_directory(CURRENT_PATH/VCS_PATH/VCS_STAGED_STATE);
}

void restore(std::filesystem::path filename)
// Discard all changes that were made after the last commit
// filename is path relative to CURRENT_PATH
{
    if (!std::filesystem::exists(CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE))
        throw Exception{"Missing File Error: cannot restore file that was never commited", CURRENT_FILENAME};

    remove_file_from_directory(CURRENT_PATH/filename);
    copy_file_to_directory(CURRENT_PATH/VCS_PATH/VCS_COMMITED_STATE/filename, CURRENT_PATH);
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
        else if (INPUT_CURRENT_COMMAND == COMMIT)
            commit(repo, argv[INPUT_COMMAND_INDEX + 1]);
        else if (INPUT_CURRENT_COMMAND == RESTORE)
            restore(argv[INPUT_COMMAND_INDEX + 1]); 

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