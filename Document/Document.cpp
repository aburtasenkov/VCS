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

LineClass::Line& DocumentClass::Document::operator[](int index)
{
    if (index < 0) throw std::runtime_error("LineClass::line::operator[index]: index < 0.");

    if (!index < size())
        return *(new LineClass::Line{});    // LEAKING MEMORY
    
    auto object_iterator = lines.begin();
    while(index > 0)
    {
        ++object_iterator;
        --index; 
    }
    return *object_iterator;
}
