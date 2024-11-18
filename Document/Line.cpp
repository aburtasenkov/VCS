#include "Line.hpp"

Line_Namespace::Line::iterator Line_Namespace::Line::begin()
{
    return words.begin();
}

Line_Namespace::Line::iterator Line_Namespace::Line::end()
{
    return words.end();
}

Line_Namespace::Line::Line()
    :words{}
{
}

Line_Namespace::Line::Line(const std::string& line)
{
    std::istringstream iss{line};
    std::string word;

    while (iss >> word)
        words.push_back(word);
}

Line_Namespace::Line::Line(const std::vector<std::string>& const_ref)
    :words{const_ref}
{
}

bool Line_Namespace::Line::operator==(Line& other)
{
    // if size doesn't match
    if (size() != other.size())
        return false;
    // Check each word
    return std::equal(words.begin(), words.end(), other.begin());
}

bool Line_Namespace::Line::operator!=(Line& other)
{
    return !(*this == other);
}


std::string& Line_Namespace::Line::operator[](int index)
// Range-checked operation
// Returns non-const value
{
    if (0 < index || index >= words.size()) throw std::runtime_error{"Line::operator[](int index) - index out of range"};
    return words[index];
}

const std::string& Line_Namespace::Line::operator[](int index) const
// Range-checked operation
// Returns const value
{
    if (0 < index || index >= words.size()) throw std::runtime_error{"Line::operator[](int index) - index out of range"};
    return words[index];
}

int Line_Namespace::Line::size()
{
    return words.size();
}

std::ostream& Line_Namespace::operator<<(std::ostream& os, Line& line)
{
    auto begin = line.begin();

    while (begin != line.end()) 
    {
        // if there are more than 1 word left in line
        // otherwise - extra whitespace at the end of the line
        if (line.end() - begin != 1)
            os << *begin << ' ';
        else
            os << *begin;
        ++begin;
    }
    return os;
}