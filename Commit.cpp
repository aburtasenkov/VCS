#include "Commit.hpp"

/*--------------------------------Commit Initializers----------------------------------------------------------------------------*/

Commit_Namespace::Commit::Commit()
    :commit_message("NO_MESSAGE")   
    {
        // Convert to time_t to get a readable time
        std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        // Convert to tm struct to access individual date and time components
        timepoint = *(std::localtime(&time));
    }

Commit_Namespace::Commit::Commit(const std::string& message)
    :commit_message(message)    
    {
        // Convert to time_t to get a readable time
        std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        // Convert to tm struct to access individual date and time components
        timepoint = *(std::localtime(&time));
    }

/*-----------------------------------------------------------------------------------------------------------------------*/

void Commit_Namespace::Commit::push_back(const Commit_Namespace::Filechange& fc)
{
    modified_files.push_back(fc);
}

/*-------------------------------------------Private member methods----------------------------------------------------------------------------*/

std::ostream& Commit_Namespace::operator<<(std::ostream& os, const Commit& c)
{
    os << c.timepoint << " " << c.commit_message << ' ';
    for (int index = 0; index < c.modified_files.size(); ++index)
    {
        os << c.modified_files[index];
        // if not last add whitespace
        if (index < c.modified_files.size() - 1)
            os << ' ';
    }
    return os;
}

std::ostream& Commit_Namespace::operator<<(std::ostream& os, const Filechange& c)
{
    os << c.source << ' ' << c.changes;
    return os;
}

std::istream& Commit_Namespace::operator>>(std::istream& is, Filechange& c)
{
    is >> c.source >> c.changes;
    c.source = ignore_char(c.source, '"');  //solves obscure bug of any other Filechange other than first having \" at the end of c.source 
    return is;
}

std::istream& Commit_Namespace::operator>>(std::istream& is, Commit& c)
{
    is >> c.timepoint >> c.commit_message;
    while (is.good())
    {
        Filechange fc;
        is >> fc;
        c.push_back(fc);
    }
    return is;
}

std::istream& Commit_Namespace::operator>>(std::istream& is, std::tm& timepoint)
{
    char dot1, dot2, colon1, colon2;
    is >> timepoint.tm_mday >> dot1 >> timepoint.tm_mon >> dot2 >> timepoint.tm_year;
    is >> timepoint.tm_hour >> colon1 >> timepoint.tm_min >> colon2 >> timepoint.tm_sec;
    timepoint.tm_mon -= 1; // months are 0-based
    timepoint.tm_year -= 1900; // years since 1900

    if (is.fail() || dot1 != '.' || dot2 != '.' || colon1 != ':' || colon2 != ':')
        throw std::runtime_error{"Input Error: wrong formatted time"};
    return is;
}

std::ostream& Commit_Namespace::operator<<(std::ostream& os, const std::tm& timepoint)
{
    return os << std::put_time(&timepoint, "%d.%m.%Y %H:%M:%S");
}