#include "Document/Document.hpp"

/*
Document is changed pattern:

{ *PATH* { *REMOVED LINES* } { *ADDED LINES* } }
*/

namespace DocumentComparisonClass
{
    class DocumentComparison
    {
        public:
            DocumentComparison(DocumentClass::Document& original_state, DocumentClass::Document& changed_state);

            const std::vector<std::pair<LineClass::Line, int>>& get_added_lines() { return added_lines; }
            const std::vector<int>& get_removed_lines() { return removed_lines; }

            bool is_changed() 
            { 
                return ( ( added_lines.size() || removed_lines.size() ) ? true : false );
            }

            bool is_inserted(DocumentClass::Document& doc, LineClass::Line& line, int index);
        private:
            std::vector<std::pair<LineClass::Line, int>> added_lines;    // stores lines that were added at index int
            std::vector<int> removed_lines; // stores indexes of lines that were removed
    };

    bool is_document_changed(DocumentClass::Document& original_state, DocumentClass::Document& changed_state);
};