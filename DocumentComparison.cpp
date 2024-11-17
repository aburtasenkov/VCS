#include "DocumentComparison.hpp"

DocumentComparisonClass::DocumentComparison::DocumentComparison(DocumentClass::Document& original_state, DocumentClass::Document& changed_state)
// Compares 2 documents for changes on initialization
{
    // iterate through each line
    for (int index_line = 0; index_line < original_state.size(); ++index_line)
    {
        int original_state_line_words_count = original_state[index_line].get_container().size();
        int changed_state_line_words_count = changed_state[index_line].get_container().size();

        // Not same amount of words
        if (original_state_line_words_count != changed_state_line_words_count)
        {
            added_lines.push_back({changed_state[index_line], index_line});
            removed_lines.push_back(index_line);
            continue;
        }

        //  iterate and compare each word together
        for (int index_word = 0; index_word < original_state_line_words_count; ++index_word)
        {
            if (original_state[index_line][index_word] != changed_state[index_line][index_word])
            {
                added_lines.push_back({changed_state[index_line], index_line});
                removed_lines.push_back(index_line);
                break;  // Go to next line
            }
        }
    }
}
