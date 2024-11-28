#include "Commit.hpp"

/*--------------------------------Commit Initializers----------------------------------------------------------------------------*/

Commit_Namespace::Commit::Commit()
    :commit_message("NO_MESSAGE")   {   }

Commit_Namespace::Commit::Commit(const std::string& message)
    :commit_message(message)    {   }

/*-----------------------------------------------------------------------------------------------------------------------*/

void Commit_Namespace::Commit::push_back(const Commit_Namespace::Filechange& fc)
{
    modified_files.push_back(fc);
}

/*-------------------------------------------Private member methods----------------------------------------------------------------------------*/

std::ostream& Commit_Namespace::operator<<(std::ostream& os, const Commit& c)
{
    os << c.hash_index << " " << c.commit_message << ' ';
    for (int index = 0; index < c.modified_files.size(); ++index)
    {
        os << c.modified_files[index];
        if (index < c.modified_files.size() - 1)
            os << ' ';
    }
    return os;
}

std::ostream& Commit_Namespace::operator<<(std::ostream& os, const Filechange& c)
{
    os << c.source << ' ' << c.modified << ' ' << c.changes;
    return os;
}

std::istream& Commit_Namespace::operator>>(std::istream& is, Filechange& c)
{
    is >> c.source >> c.modified >> c.changes;
    return is;
}

std::istream& Commit_Namespace::operator>>(std::istream& is, Commit& c)
{
    is >> c.hash_index >> c.commit_message;
    std::string filechanges_line;
    for (Filechange fc; std::getline(is, filechanges_line); fc = Filechange{})
    {
        std::istringstream iss{filechanges_line};
        iss >> fc;
        c.push_back(fc);
    }
    return is;
}