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

std::filesystem::path Document_Namespace::Document::get_path()
{
    return filepath;
}

Document_Namespace::DocumentComparison::DocumentComparison(Document_Namespace::Document& source, Document_Namespace::Document& modified)
    :source_filepath(source.get_path()), modified_filepath(modified.get_path())
// Compares 2 documents for changes on initialization
{
    push_back_inserted(source, modified);
    push_back_removed(source, modified);
}

void Document_Namespace::DocumentComparison::push_back_inserted(Document_Namespace::Document& source, Document_Namespace::Document& modified)
{
    int index = 0;
    // if source doesn't contain any line of modified -> new line was added to modified
    for (auto& line : modified)
    {
        if (!contains(source, line))
            inserted.push_back({line, index});
        ++index;
    }
}

void Document_Namespace::DocumentComparison::push_back_removed(Document_Namespace::Document& source, Document_Namespace::Document& modified)
{
    int index = 0;
    // if modified doesn't contain any line of source -> a line was removed from source
    for (auto& line : source)
    {
        if (!contains(modified, line))
            removed.push_back(index);
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


std::ostream& Document_Namespace::DocumentComparison::output_inserted(std::ostream& os)
{
    os << "{ ";
    for (auto& pair : inserted)
    {
        os << "{ " << pair.first << " " << pair.second << " } ";
    }
    os << "}";
    return os;
}

std::ostream& Document_Namespace::DocumentComparison::output_removed(std::ostream& os)
{
    os << "{ ";
    for (int index : removed)
    {
        os << "{ " << index << " } ";
    }
    os << "}";
    return os;
}

std::ostream& Document_Namespace::DocumentComparison::output(std::ostream& os, Document_Namespace::Linetype type)
{
    if (type == Document_Namespace::Linetype::inserted)
    {
        return output_inserted(os);
    }
    else if (type == Document_Namespace::Linetype::removed)
    {
        return output_removed(os);
    }
    else throw std::runtime_error("std::ostream& Document_Namespace::DocumentComparison::output(std::ostream& os, Document_Namespace::Linetype type): bad type parameter");
}

std::filesystem::path Document_Namespace::DocumentComparison::get_path(Document_Namespace::Filetype type)
{
    if (type == Document_Namespace::Filetype::source)
        return source_filepath;
    else if (type == Document_Namespace::Filetype::modified)
        return modified_filepath;
    else throw std::runtime_error("std::filesystem::path Document_Namespace::DocumentComparison::get_path(Document_Namespace::Filetype type): bad type parameter");
}

bool Document_Namespace::DocumentComparison::is_modified()
{ 
    return ( ( inserted.size() || removed.size() ) ? true : false ); 
}