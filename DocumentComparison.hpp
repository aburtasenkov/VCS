#include "Document/Document.hpp"

namespace DocumentComparisonClass
{
    class DocumentComparison
    {
        private:
            std::vector<std::pair<LineClass::Line, int>> added_lines;    // stores lines that were added at index int
            std::vector<int> removed_lines; // stores indexes of lines that were removed
    };

    bool is_document_changed(DocumentClass::Document& original_state, DocumentClass::Document& changed_state);
};