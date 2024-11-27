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
    for (const Filechange& file : c.modified_files)
    {
        os << file << ' ';
    }
    return os;
}

std::ostream& Commit_Namespace::operator<<(std::ostream& os, const Filechange& c)
{
    os << c.source << " " << c.modified << ' ' << c.changes;
    return os;
}

std::string ignore_char(const std::string& str, const char& ignore)
{
    std::string output;
    for (const char& ch : str)
    {
        if (ch != ignore)
            output += ch;
    }
    return output;
}

std::istream& Commit_Namespace::operator>>(std::istream& is, Filechange& c)
{
    std::string source, modified;
    is >> source >> modified >> c.changes;
    c.source = ignore_char(source, '"');
    c.modified = ignore_char(modified, '"');
    return is;
}

std::istream& Commit_Namespace::operator>>(std::istream& is, Commit& c)
{
    is >> c.hash_index >> c.commit_message;
    Filechange changes{};
    while (is >> changes)
    {
        std::cout << changes;
        c.push_back(changes);
    }
    return is;
}