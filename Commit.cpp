#include "Commit.hpp"

/*--------------------------------Commit Initializers----------------------------------------------------------------------------*/

Commit_Namespace::Commit::Commit()
    :timepoint(std::chrono::system_clock::now().time_since_epoch())    {   }

/*-----------------------------------------------------------------------------------------------------------------------*/

void Commit_Namespace::Commit::push_back(const Commit_Namespace::Filechange& fc)
{
    modified_files.push_back(fc);
}

/*-------------------------------------------Private member methods----------------------------------------------------------------------------*/

int Commit_Namespace::Commit::hash() const
{
    return timepoint.time_since_epoch().count();
}

std::ostream& Commit_Namespace::operator<<(std::ostream& os, const Commit& c)
{
    os << "{ " << c.hash() << " ";
    for (const Filechange& file : c.modified_files)
    {
        os << "{ ";
        os << file.source.get_path() << " ";
        os << file.modified.get_path() << " ";
        os << file.changes;
        os << " } ";
    }
    return os << "}";
}