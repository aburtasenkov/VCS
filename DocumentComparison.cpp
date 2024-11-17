#include "DocumentComparison.hpp"

DocumentComparisonClass::DocumentComparison::DocumentComparison(DocumentClass::Document& original_state, DocumentClass::Document& changed_state)
// Compares 2 documents for changes on initialization
{
    // iterate through each line
    for (int index_line = 0; index_line < original_state.size(); ++index_line)
    {
        if (!(original_state[index_line] == changed_state[index_line]))
        {
            added_lines.push_back({changed_state[index_line], index_line});
            removed_lines.push_back(index_line);
        }
    }
}

bool DocumentComparisonClass::is_inserted(DocumentClass::Document& doc, LineClass::Line& line, int index)
// Possibly wrong code idk didnt check
{
    for (;index < doc.size(); ++index)
    {
        if (doc[index] == line)
        {
            return true;
        }
    }
    return false;
}