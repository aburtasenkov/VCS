#include "Line.hpp"

LineClass::Line::Line()
    :words{}
{
}

LineClass::Line::Line(const std::string& line)
{
    std::istringstream iss{line};
    std::string word;

    while (iss >> word)
        words.push_back(word);
}

LineClass::Line::Line(const std::vector<std::string>& const_ref)
    :words{const_ref}
{
}


std::string& LineClass::Line::operator[](int i)
// Range-checked operation
// Returns non-const value
{
    if (0 < i || i >= words.size()) throw std::runtime_error{"Line::operator[](int index) - index out of range"};
    return words[i];
}

const std::string& LineClass::Line::operator[](int i) const
// Range-checked operation
// Returns const value
{
    if (0 < i || i >= words.size()) throw std::runtime_error{"Line::operator[](int index) - index out of range"};
    return words[i];
}

void LineClass::Line::push_back(const std::string& string)
{
    words.push_back(string);
}
    
std::vector<std::string>& LineClass::Line::get_container()
{
    return words;
}

std::ostream& LineClass::operator<<(std::ostream& os, Line ll)
{
    os << '"';
    for (auto string : ll.get_container()) 
    {
        os << string << ' ';
    }
    return os << '"';
}