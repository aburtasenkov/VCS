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
    os << c.hash_index << " " << c.commit_message << std::endl;
    for (const Filechange& file : c.modified_files)
    {
        os << file << std::endl;
    }
    return os;
}

std::ostream& Commit_Namespace::operator<<(std::ostream& os, const Filechange& c)
{
    os << c.source << " " << c.modified << "\n";
    os << c.changes;
    return os;
}

std::istream& Commit_Namespace::operator>>(std::istream& is, Filechange& c)
{
    std::string line;
    is >> c.source >> c.modified;
    std::getline(is, line, '\n');
    is >> c.changes;
    return is;
}

std::istream& Commit_Namespace::operator>>(std::istream& is, Commit& c)
{
    c.modified_files.clear();
    char ch;
    is >> c.hash_index >> c.commit_message;
    while (is >> ch)
    {
        is.putback(ch);
        Filechange changes;
        is >> changes;
        c.push_back(changes);
    }
    return is;
}