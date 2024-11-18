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
    Document is changed pattern:

    { *PATH* { *REMOVED LINES* } { *ADDED LINES* } }
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
        private:
            void push_back_added_lines(Document_Namespace::Document& original_state, Document_Namespace::Document& changed_state);
            void push_back_removed_lines(Document_Namespace::Document& original_state, Document_Namespace::Document& changed_state);

            std::vector<std::pair<Line_Namespace::Line, int>> added_lines;    // stores lines that were added at index int
            std::vector<int> removed_lines; // stores indexes of lines that were removed
    };

    bool contains(Document_Namespace::Document& doc, Line_Namespace::Line& line);
}
