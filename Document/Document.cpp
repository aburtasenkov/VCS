#include "Document.hpp"

Document_Namespace::Document::iterator Document_Namespace::Document::begin()
{
    return lines.begin();
}

Document_Namespace::Document::iterator Document_Namespace::Document::end()
{
    return lines.end();
}

Document_Namespace::Document::Document()
{
}

Document_Namespace::Document::Document(std::istream& is)
{
    std::string line;
    while (std::getline(is, line))
    {
        lines.push_back(Line_Namespace::Line{line});
    }
}

Document_Namespace::Document::Document(const std::filesystem::path& path_to_input_file)
{
    std::string input = static_cast<std::string>(path_to_input_file);
    std::ifstream ifs{input};
    *this = Document_Namespace::Document(ifs);
}

Line_Namespace::Line& Document_Namespace::Document::operator[](int index)
{
    if (index < 0) throw std::runtime_error("Document_Namespace::Document::operator[](int index): index smaller than 0");
    auto p = lines.begin();
    while (index != 0)
    {
        ++p;
        --index;
    }
    return *p;
}

int Document_Namespace::Document::size() const
{
    return lines.size();
}

Document_Namespace::DocumentComparison::DocumentComparison(Document_Namespace::Document& original_state, Document_Namespace::Document& changed_state)
// Compares 2 documents for changes on initialization
{
    push_back_added_lines(original_state, changed_state);
    push_back_removed_lines(original_state, changed_state);
}

void Document_Namespace::DocumentComparison::push_back_added_lines(Document_Namespace::Document& original_state, Document_Namespace::Document& changed_state)
{
    int index = 0;
    // if original_state doesn't contain any line of changed_state -> new line was added to changed_state
    for (auto& line : changed_state)
    {
        if (!contains(original_state, line))
            added_lines.push_back({line, index});
        ++index;
    }
}

void Document_Namespace::DocumentComparison::push_back_removed_lines(Document_Namespace::Document& original_state, Document_Namespace::Document& changed_state)
{
    int index = 0;
    // if changed_state doesn't contain any line of original_state -> a line was removed from original_state
    for (auto& line : original_state)
    {
        if (!contains(changed_state, line))
            removed_lines.push_back(index);
        ++index;
    }
}

bool Document_Namespace::contains(Document_Namespace::Document& doc, Line_Namespace::Line& line)
{
    for (auto& l : doc)
    {
        if (l == line)
            return true;
    }
    return false;
}