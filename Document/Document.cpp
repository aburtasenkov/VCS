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

DocumentClass::Document& DocumentClass::Document::operator=(DocumentClass::Document&& other)
{
    lines = std::move(other.lines);
    return *this;
}
