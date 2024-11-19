#include "Commit.hpp"

/*--------------------------------Commit Initializers----------------------------------------------------------------------------*/

Commit_Namespace::Commit::Commit()
    :timepoint(std::chrono::system_clock::now().time_since_epoch())    {   }

/*-----------------------------------------------------------------------------------------------------------------------*/

void Commit_Namespace::Commit::push_back(const Commit_Namespace::Filechange& fc)
{
    modified_files.push_back(fc);
}

/*-----------------------------------------------------------------------------------------------------------------------*/

std::ostream& Commit_Namespace::Commit::output(std::ostream& os, const std::string& indentation) const
{
    os << "{ " << hash() << "\n";
    for (const Filechange& file : modified_files)
    {
        os << indentation << "{\n";
        os << indentation << file.source.get_path() << "\n";
        os << indentation << file.modified.get_path() << "\n";
        os << indentation << indentation; file.changes.output(std::cout, Document_Namespace::Linetype::removed); os << "\n\t\t";
        file.changes.output(std::cout, Document_Namespace::Linetype::inserted, "\n\t\t"); os << "\n";
        os << indentation << "}\n";
    }
    return os << "}";
}

/*-------------------------------------------Private member methods----------------------------------------------------------------------------*/

int Commit_Namespace::Commit::hash() const
{
    return timepoint.time_since_epoch().count();
}