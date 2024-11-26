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
    os << "{ ";
    os << c.source.get_path() << " ";
    os << c.modified.get_path() << " ";
    os << c.changes;
    os << " } ";
    return os;
}