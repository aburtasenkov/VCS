#include "DocumentComparison.hpp"

DocumentComparisonClass::DocumentComparison::DocumentComparison(DocumentClass::Document& original_state, DocumentClass::Document& changed_state)
// Compares 2 documents for changes on initialization
{
    // iterate through each line

    for (int index_line = 0; index_line < std::min(original_state.size(), changed_state.size()); ++index_line)
    {
        added_lines.push_back({changed_state[index_line], index_line});
        removed_lines.push_back(index_line);
    }
}

bool DocumentComparisonClass::contains(DocumentClass::Document::iterator b, DocumentClass::Document::iterator e, LineClass::Line& line)
{
    while (b != e)
    {
        if (*b == line)
            return true;
        ++b;
    }
    return false;
}