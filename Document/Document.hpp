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
        Document(std::istream& is);
        Document(const std::filesystem::path& path_to_input_file);
        
        Line_Namespace::Line& operator[](int index);

        int size() const;
    private: 
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

    class DocumentComparison
    {
        public:
            DocumentComparison(Document_Namespace::Document& original_state, Document_Namespace::Document& changed_state);

            const std::vector<std::pair<Line_Namespace::Line, int>>& get_added_lines() { return added_lines; }
            const std::vector<int>& get_removed_lines() { return removed_lines; }

            bool is_changed() 
            { 
                return ( ( added_lines.size() || removed_lines.size() ) ? true : false );
            }

            std::ostream& output_added_lines(std::ostream& os);
            std::ostream& output_removed_lines(std::ostream& os);
        private:
            void push_back_added_lines(Document_Namespace::Document& original_state, Document_Namespace::Document& changed_state);
            void push_back_removed_lines(Document_Namespace::Document& original_state, Document_Namespace::Document& changed_state);

            std::vector<std::pair<Line_Namespace::Line, int>> added_lines;    // stores lines that were added at index int
            std::vector<int> removed_lines; // stores indexes of lines that were removed
    };

    bool contains(Document_Namespace::Document& doc, Line_Namespace::Line& line);
}
