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
    std::ifstream ifs{filepath};

    Document_Namespace::Document::value_type line;
    while (std::getline(ifs, line))
    {
        lines.push_back(line);
    }
}

/*------------------------------------Indexing---------------------------------------------------------*/

Document_Namespace::Document::value_type& Document_Namespace::Document::operator[](int index)
// range checked indexing
// non const indexing
{
    if (0 < index || index >= lines.size()) throw std::runtime_error{"Document::operator[](int index) - index out of range"};
    return lines[index];
}

const Document_Namespace::Document::value_type& Document_Namespace::Document::operator[](int index) const
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
        if (std::find(source.begin(), source.end(), line) == source.end())
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
        if (std::find(modified.begin(), modified.end(), line) == modified.end())
            removed.push_back({line, index});
        ++index;
    }
}

/*-------------------------------------------private output methods--------------------------------------------------*/

std::ostream& Document_Namespace::DocumentComparison::output_inserted(std::ostream& os) const
{
    os << '{';
    for (const auto& pair : inserted)
    {
        os << "{{" << pair.first << "}" << pair.second << "}";
    }
    os << '}';
    return os;
}

std::ostream& Document_Namespace::DocumentComparison::output_removed(std::ostream& os) const
{
    os << '{';
    for (const auto& pair : removed)
    {
        os << "{{" << pair.first << "}" << pair.second << "}";
    }
    os << '}';
    return os;
}

std::ostream& Document_Namespace::operator<<(std::ostream& os, const Document_Namespace::DocumentComparison& changes)
{
    changes.output_removed(os);
    os << '/';
    changes.output_inserted(os);
    return os;
}

bool get_line_changes(std::istream& is, Document_Namespace::DocumentComparison::value_type& pair)
{
    pair.first = Document_Namespace::Document::value_type{};
    // if next char is a closing bracket -> no modified lines
    if (next_char_is(is, '}') || next_char_is(is, '/'))
        return false;

    char delim1, delim2, delim3, delim4;
    is >> delim1 >> delim2;
    input_until_char(is, pair.first, '}');
    is >> delim3 >> pair.second >> delim4;

    if (!(is_curly_bracket(delim1) && is_curly_bracket(delim2) && is_curly_bracket(delim3) && is_curly_bracket(delim4)))
        return false;

    return true;
}

std::istream& Document_Namespace::operator>>(std::istream& is, DocumentComparison& changes)
{
    auto* container = &changes.removed;
    for (int i = 0; i < 2; ++i) // do for 2 containers
    {
        char ch;
        is >> ch;
        Document_Namespace::DocumentComparison::value_type pair;
        while (get_line_changes(is, pair))
            container->push_back(pair);
        is >> ch >> ch;
        container = &changes.inserted;
    }

    return is;
}

Document_Namespace::Document Document_Namespace::operator+(Document_Namespace::Document doc, Document_Namespace::DocumentComparison& changes)
// Add changes to a document
{
    auto& container = changes.data(Document_Namespace::Linetype::removed);
    for (auto& [line, index] : container)
        doc.erase(doc.begin() + index);

    container = changes.data(Document_Namespace::Linetype::inserted);
    for (auto& [line, index] : container)
        doc.insert(doc.begin() + index, line);

    return doc;
}

Document_Namespace::Document Document_Namespace::operator-(Document_Namespace::Document doc, Document_Namespace::DocumentComparison& changes)
// discard changes from a document
{
    auto& container = changes.data(Document_Namespace::Linetype::inserted);
    for (auto& [line, index] : container)
        doc.erase(doc.begin() + index);

    container = changes.data(Document_Namespace::Linetype::removed);
    for (auto& [line, index] : container)
        doc.insert(doc.begin() + index, line);

    return doc;
}

std::vector<Document_Namespace::DocumentComparison::value_type>& Document_Namespace::DocumentComparison::data(Document_Namespace::Linetype lt)
// return reference to container containing lt information
{
    if (lt == Document_Namespace::Linetype::inserted)
        return inserted;
    if (lt == Document_Namespace::Linetype::removed)
        return removed;
    throw std::runtime_error("DocumentComparison::data - bad input");
}