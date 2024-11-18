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


std::string& Line_Namespace::Line::operator[](int i)
// Range-checked operation
// Returns non-const value
{
    if (0 < i || i >= words.size()) throw std::runtime_error{"Line::operator[](int index) - index out of range"};
    return words[i];
}

const std::string& Line_Namespace::Line::operator[](int i) const
// Range-checked operation
// Returns const value
{
    if (0 < i || i >= words.size()) throw std::runtime_error{"Line::operator[](int index) - index out of range"};
    return words[i];
}

int Line_Namespace::Line::size()
{
    return words.size();
}

std::ostream& Line_Namespace::operator<<(std::ostream& os, Line ll)
{
    os << '"';
    auto b = ll.begin();
    auto e = ll.end();

    while (b != e) 
    {
        os << *b << ' ';
        ++b;
    }
    return os << '"';
}