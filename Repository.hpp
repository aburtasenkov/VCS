#include <string>
#include "Commit.hpp"

class Repository{
public:
    Repository(const std::string& repo_name);

    const std::string& get_name() { return name; };
    const std::vector<Commit_Namespace::Commit>& get_commits() { return commits; }
private:
    std::string name;
    std::vector<Commit_Namespace::Commit> commits;
};

Repository::Repository(const std::string& repo_name)
    :name(repo_name)
{   }
