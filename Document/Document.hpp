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
        iterator begin();
        iterator end();

        // User - Interface
        Document();
        Document(const std::filesystem::path& path_to_input_file);
        
        Line_Namespace::Line& operator[](int index);

        int size() const;
        std::filesystem::path get_path();
    private: 
        std::filesystem::path filepath;
        std::vector<Line_Namespace::Line> lines;
    };

    /*
    Document changes pattern stored in .change files that are named by hash value of commit:

    A single Commit followed by another commit:
    {
        HASH { 
            FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
             {
             FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
    }
    {
        HASH { 
            FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
             {
             FILEPATH
                { INDEX INDEX } 
                { { ADDED_LINE INDEX } { ADDED_LINE INDEX } } 
             }
    }
    */

    enum class Filetype
    {
        source, modified
    };

    enum class Linetype
    {
        inserted,
        removed
    };

    class DocumentComparison
    {
        public:
            DocumentComparison(Document_Namespace::Document& source, Document_Namespace::Document& modified);

            std::ostream& output(std::ostream& os, Linetype type);

            bool is_modified();

            // Get methods
            std::filesystem::path get_path(Filetype type);
            const std::vector<std::pair<Line_Namespace::Line, int>>& get_inserted() { return inserted; }
            const std::vector<int>& get_removed() { return removed; }
        private:
            std::filesystem::path source_filepath;
            std::filesystem::path modified_filepath;
            std::vector<std::pair<Line_Namespace::Line, int>> inserted;    // stores lines that were added at index int
            std::vector<int> removed; // stores indexes of lines that were removed

            void push_back_inserted(Document_Namespace::Document& source, Document_Namespace::Document& modified);
            void push_back_removed(Document_Namespace::Document& source, Document_Namespace::Document& modified);

            std::ostream& output_inserted(std::ostream& os);
            std::ostream& output_removed(std::ostream& os);
    };

    bool contains(Document_Namespace::Document& doc, Line_Namespace::Line& line);
}
