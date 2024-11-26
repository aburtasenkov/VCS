#include "Document.hpp"

/*----------------------------------------Document Class-----------------------------------------------------*/
/*----------------------------------------Document iterators-----------------------------------------------------*/

Document_Namespace::Document::iterator Document_Namespace::Document::begin()
{
    return lines.begin();
}

Document_Namespace::Document::iterator Document_Namespace::Document::end()
{
    return lines.end();
}

Document_Namespace::Document::const_iterator Document_Namespace::Document::begin() const
{
    return lines.begin();
}

Document_Namespace::Document::const_iterator Document_Namespace::Document::end() const
{
    return lines.end();
}

/*--------------------------------------Document initilizers-------------------------------------------------------*/

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
        lines.push_back(line);
    }
}

/*------------------------------------Indexing---------------------------------------------------------*/

std::string& Document_Namespace::Document::operator[](int index)
// range checked indexing
// non const indexing
{
    if (0 < index || index >= lines.size()) throw std::runtime_error{"Document::operator[](int index) - index out of range"};
    return lines[index];
}

const std::string& Document_Namespace::Document::operator[](int index) const
// range checked indexing
// const indexing
{
    if (0 < index || index >= lines.size()) throw std::runtime_error{"Document::operator[](int index) - index out of range"};
    return lines[index];
}

/*---------------------------------------------------------------------------------------------*/

int Document_Namespace::Document::size() const
{
    return lines.size();
}

const std::filesystem::path& Document_Namespace::Document::get_path() const
{
    return filepath;
}

/*---------------------------------------------------------------------------------------------*/

std::ostream& Document_Namespace::operator<<(std::ostream& os, const Document& doc)
{
    for (const auto& line : doc)
    {
        os << line << "\n";
    }
    return os;
}

/*--------------------------------------DocumentComparison Class-------------------------------------------------------*/
/*----------------------------------------------DocumentComparison initializer-----------------------------------------------*/

Document_Namespace::DocumentComparison::DocumentComparison(const Document_Namespace::Document& source, const Document_Namespace::Document& modified)
// Compares 2 documents for changes on initialization
{
    push_back_inserted(source, modified);
    push_back_removed(source, modified);
}

/*---------------------------------------------------------------------------------------------*/

bool Document_Namespace::DocumentComparison::is_modified() const    
{ 
    return ( ( inserted.size() || removed.size() ) ? true : false ); 
}

/*-------------------------------------Private methods--------------------------------------------------------*/

void Document_Namespace::DocumentComparison::push_back_inserted(const Document_Namespace::Document& source, const Document_Namespace::Document& modified)
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

void Document_Namespace::DocumentComparison::push_back_removed(const Document_Namespace::Document& source, const Document_Namespace::Document& modified)
{
    int index = 0;
    // if modified doesn't contain any line of source -> a line was removed from source
    for (auto& line : source)
    {
        if (!contains(modified, line))
            removed.push_back({line, index});
        ++index;
    }
}

/*---------------------------------------------------------------------------------------------*/

bool Document_Namespace::contains(const Document_Namespace::Document& doc, const std::string& line)
{
    for (const auto& l : doc)
    {
        if (l == line)
            return true;
    }
    return false;
}

/*-------------------------------------------private output methods--------------------------------------------------*/

std::ostream& Document_Namespace::DocumentComparison::output_inserted(std::ostream& os) const
{
    for (const auto& pair : inserted)
    {
        os << "{{" << pair.first << "}" << pair.second << "}";
    }
    return os;
}

std::ostream& Document_Namespace::DocumentComparison::output_removed(std::ostream& os) const
{
    for (const auto& pair : removed)
    {
        os << "{{" << pair.first << "}" << pair.second << "}";
    }
    return os;
}

std::ostream& Document_Namespace::operator<<(std::ostream& os, const Document_Namespace::DocumentComparison& changes)
{
    changes.output_removed(os);
    os << "\n";
    changes.output_inserted(os);
    return os;
}

std::istream& Document_Namespace::operator>>(std::istream& is, DocumentComparison& changes)
{
    changes.clear();    // clear because vectors arent changed, only modified
    char ch;
    std::string line;
    int line_index;

    std::getline(is, line, '\n');   // go to the end of the line of source and modified paths
    std::getline(is, line);   // get the first line of the output which are removed lines
    std::istringstream removed_lines{line};
    while (removed_lines >> ch)
    {
        removed_lines.putback(ch);
        removed_lines >> ch >> ch;
        std::getline(removed_lines, line, '}');
        removed_lines >> line_index >> ch;
        changes.removed.push_back({line, line_index});
    }

    // removes a bug of buffer going push backed into the vector, idk why
    line = "";
    line_index = 0;

    std::getline(is, line);
    std::istringstream inserted_lines{line};
    while (inserted_lines >> ch)
    {
        inserted_lines.putback(ch);
        inserted_lines >> ch >> ch;
        std::getline(inserted_lines, line, '}');
        inserted_lines >> line_index >> ch;
        changes.inserted.push_back({line, line_index});
    }
    return is;
}