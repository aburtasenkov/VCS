#include "Document.hpp"

DocumentClass::Document::Document()
{
}

DocumentClass::Document::Document(std::istream& is)
{
    std::string line;
    while (std::getline(is, line))
    {
        lines.push_back(LineClass::Line{line});
    }
}

DocumentClass::Document& DocumentClass::Document::operator=(DocumentClass::Document&& other)
{
    lines = std::move(other.lines);
    return *this;
}