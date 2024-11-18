#include <list>
#include <filesystem>
#include <fstream>
#include "Line.hpp"

namespace Document_Namespace
{
    class Document{
    public:
        // STL - Interface
        typedef std::vector<Line_Namespace::Line>::iterator iterator;
        typedef std::vector<Line_Namespace::Line>::const_iterator const_iterator;
        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const ;

        // User - Interface
        Document();
        Document(const std::filesystem::path& path_to_input_file);
        
        Line_Namespace::Line& operator[](int index);
        const Line_Namespace::Line& operator[](int index) const;

        int size() const;
        const std::filesystem::path& get_path() const;
    private: 
        std::filesystem::path filepath;
        std::vector<Line_Namespace::Line> lines;
    };

    /*
    Document changes pattern stored in .change files that are named by hash value of commit:

    A single Commit followed by another commit:
    {
        HASH { 
            SOURCE_FILEPATH
            MODIFIED_FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
             {
            SOURCE_FILEPATH
            MODIFIED_FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
    }
    {
        HASH { 
            SOURCE_FILEPATH
            MODIFIED_FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
             {
            SOURCE_FILEPATH
            MODIFIED_FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
    }
    */

    enum class Linetype
    {
        inserted,
        removed
    };

    class DocumentComparison
    {
        public:
            DocumentComparison(const Document_Namespace::Document& source, const Document_Namespace::Document& modified);

            std::ostream& output(std::ostream& os, const Linetype& type) const ;

            bool is_modified() const;
        private:
            std::vector<std::pair<Line_Namespace::Line, int>> inserted;    // stores lines that were added at index int
            std::vector<int> removed; // stores indexes of lines that were removed

            void push_back_inserted(const Document& source, const Document& modified);
            void push_back_removed(const Document& source, const Document& modified);

            std::ostream& output_inserted(std::ostream& os) const;
            std::ostream& output_removed(std::ostream& os) const;
    };

    bool contains(const Document_Namespace::Document& doc, const Line_Namespace::Line& line);
}
