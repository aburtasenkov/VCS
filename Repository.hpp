#include "Commit.hpp"

class Repository{
public:
    Repository() {}
    Repository(const std::string& repo_name);

    void add_commit(const Commit_Namespace::Commit& com);
    friend std::istream& operator>>(std::istream& is, Repository& repo);
    friend std::ostream& operator<<(std::ostream& os, const Repository& repo);

    const std::string& get_name() { return name; };
    std::vector<Commit_Namespace::Commit>& get_commits() { return commits; }
private:
    std::string name;
    std::vector<Commit_Namespace::Commit> commits;
};

Repository::Repository(const std::string& repo_name)
    :name(repo_name)    {   }

void Repository::add_commit(const Commit_Namespace::Commit& com)
{
    commits.push_back(com);
}

std::istream& operator>>(std::istream& is, Repository& repo)
// Input data into Repository
{
    std::getline(is, repo.name);
    std::string commit_line;
    while (std::getline(is, commit_line))
    {
        std::istringstream iss{commit_line};
        Commit_Namespace::Commit commit{};
        iss >> commit;
        repo.commits.push_back(commit);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Repository& repo)
// output Repository data
{
    os << repo.name << '\n';
    for (auto& commit : repo.commits)
    {
        os << commit << '\n';
    }
    return os;
}