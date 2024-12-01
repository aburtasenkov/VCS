#include <list>
#include <filesystem>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "iostream_helper_functions.hpp"

namespace Document_Namespace
{
    class Document{
    public:
        typedef std::string value_type;

        // STL - Interface
        typedef std::vector<value_type>::iterator iterator;
        typedef std::vector<value_type>::const_iterator const_iterator;
        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const ;

        // User - Interface
        Document();
        Document(const std::filesystem::path& path_to_input_file);

        iterator erase(iterator pos) { lines.erase(pos); return pos + 1; }
        iterator insert(iterator pos, const value_type& val) { lines.insert(pos, val); return pos + 1;}
        
        value_type& operator[](int index);
        const value_type& operator[](int index) const;

        int size() const;
        const std::filesystem::path& get_path() const;

        friend std::ostream& operator<<(std::ostream& os, const Document& doc);
    private: 
        std::filesystem::path filepath;
        std::vector<value_type> lines;
    };

    std::ostream& operator<<(std::ostream& os, const Document& doc);

    enum class Linetype
    {
        inserted,
        removed
    };

    class DocumentComparison
    {
        public:
            typedef std::pair<Document_Namespace::Document::value_type, int> value_type;

            DocumentComparison() {  }
            DocumentComparison(const Document& source, const Document& modified);

            friend std::ostream& operator<<(std::ostream& os, const DocumentComparison& changes);
            friend std::istream& operator>>(std::istream& is, DocumentComparison& changes);

            std::vector<value_type>& data(Linetype lt);

            bool is_modified() const;
            void clear() { inserted.clear(); removed.clear(); }
        private:
            // Line and its indexes in files
            std::vector<value_type> inserted;
            std::vector<value_type> removed;

            void push_back_inserted(const Document& source, const Document& modified);
            void push_back_removed(const Document& source, const Document& modified);

            std::ostream& output_inserted(std::ostream& os) const;
            std::ostream& output_removed(std::ostream& os) const;
    };

    bool contains(const Document& doc, const Document::value_type& line);

    std::ostream& operator<<(std::ostream& os, const DocumentComparison& changes);
    std::istream& operator>>(std::istream& is, DocumentComparison& changes);

    Document_Namespace::Document operator+(Document_Namespace::Document doc, Document_Namespace::DocumentComparison& changes);
    Document_Namespace::Document operator-(Document_Namespace::Document doc, Document_Namespace::DocumentComparison& changes);
}
