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
        // STL - Interface
        typedef std::vector<std::string>::iterator iterator;
        typedef std::vector<std::string>::const_iterator const_iterator;
        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const ;

        // User - Interface
        Document();
        Document(const std::filesystem::path& path_to_input_file);
        
        std::string& operator[](int index);
        const std::string& operator[](int index) const;

        int size() const;
        const std::filesystem::path& get_path() const;

        friend std::ostream& operator<<(std::ostream& os, const Document& doc);
    private: 
        std::filesystem::path filepath;
        std::vector<std::string> lines;
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
            DocumentComparison() {  }
            DocumentComparison(const Document_Namespace::Document& source, const Document_Namespace::Document& modified);

            friend std::ostream& operator<<(std::ostream& os, const DocumentComparison& changes);
            friend std::istream& operator>>(std::istream& is, DocumentComparison& changes);

            bool is_modified() const;
            void clear() { inserted.clear(); removed.clear(); }
        private:
            std::vector<std::pair<std::string, int>> inserted;    // stores lines that were added at index int
            std::vector<std::pair<std::string, int>> removed; // stores indexes of lines that were removed

            void push_back_inserted(const Document& source, const Document& modified);
            void push_back_removed(const Document& source, const Document& modified);

            std::ostream& output_inserted(std::ostream& os) const;
            std::ostream& output_removed(std::ostream& os) const;
    };

    bool contains(const Document_Namespace::Document& doc, const std::string& line);

    std::ostream& operator<<(std::ostream& os, const DocumentComparison& changes);
    std::istream& operator>>(std::istream& is, DocumentComparison& changes);
}
