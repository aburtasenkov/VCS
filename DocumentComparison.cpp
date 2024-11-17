#include "DocumentComparison.hpp"

DocumentComparisonClass::DocumentComparison::DocumentComparison(DocumentClass::Document& original_state, DocumentClass::Document& changed_state)
// Compares 2 documents for changes on initialization
{
    std::vector<std::pair<LineClass::Line, int>> temp_added;
    std::vector<int> temp_removed;

    // iterate through each line
    for (int index_line = 0; index_line < original_state.size(); ++index_line)
    {
        int original_state_line_words_count = original_state[index_line].get_container().size();
        int changed_state_line_words_count = changed_state[index_line].get_container().size();

        // Not same amount of words
        if (original_state_line_words_count != changed_state_line_words_count)
        {
            std::cout << "NOT SAME AMOUNT OF WORDS\n";
            temp_added.push_back({changed_state[index_line], index_line});
            temp_removed.push_back(index_line);
            continue;
        }

        std::cout << original_state_line_words_count << "\n";
        //  iterate and compare each word together
        for (int index_word = 0; index_word < original_state_line_words_count; ++index_word)
        {
            std::cout << "NEW_WORD\n";
            if (original_state[index_line][index_word] != changed_state[index_line][index_word])
            {
                std::cout << "NOT SAME WORD\n";
                temp_added.push_back({changed_state[index_line], index_line});
                temp_removed.push_back(index_line);
                break;  // Go to next line
            }
        }
    }
    added_lines = temp_added;
    removed_lines = temp_removed;
    std::cout << added_lines.size() << "\t" << removed_lines.size();
}
