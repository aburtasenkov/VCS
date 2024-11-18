#include "Commit.hpp"

void Commit_Namespace::Commit::push_back(const Commit_Namespace::Filechange& fc)
{
    modified_files.push_back(fc);
}