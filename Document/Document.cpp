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

Document_Namespace::Document::Document(const std::filesystem::path& path_to_input_file)
    :filepath(path_to_input_file)
{
    std::string input = static_cast<std::string>(filepath);
    std::ifstream ifs{input};

    std::string line;
    while (std::getline(ifs, line))
    {
        lines.push_back(Line_Namespace::Line{line});
    }
}

Line_Namespace::Line& Document_Namespace::Document::operator[](int index)
// range checked indexing
{
    if (0 < index || index >= lines.size()) throw std::runtime_error{"Document::operator[](int index) - index out of range"};
    return lines[index];
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


std::ostream& Document_Namespace::DocumentComparison::output_added_lines(std::ostream& os)
{
    os << "{ ";
    for (auto& pair : added_lines)
    {
        os << "{ " << pair.first << " " << pair.second << " } ";
    }
    os << "}";
    return os;
}

std::ostream& Document_Namespace::DocumentComparison::output_removed_lines(std::ostream& os)
{
    os << "{ ";
    for (int index : removed_lines)
    {
        os << "{ " << index << " } ";
    }
    os << "}";
    return os;
}
