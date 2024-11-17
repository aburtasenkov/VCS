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

DocumentClass::Document::Document(const std::filesystem::path& path_to_input_file)
{
    std::string input = static_cast<std::string>(path_to_input_file);
    std::ifstream ifs{input};
    *this = DocumentClass::Document(ifs);
}

LineClass::Line& DocumentClass::Document::operator[](int index)
{
    if (index < 0) throw std::runtime_error("DocumentClass::Document::operator[](int index): index smaller than 0");
    if (index = 0)
        return lines.front();
    return this->operator[](index - 1);
}
