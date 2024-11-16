#include "Document/Document.hpp"

namespace DocumentComparisonClass
{
    class DocumentComparison
    {
        private:
            std::vector<std::pair<LineClass::Line, int>> added_lines;    // stores lines that were added at index int
            std::vector<int> removed_lines; // stores indexes of lines that were removed
    };

    bool is_document_changed(DocumentClass::Document& original_state, DocumentClass::Document& changed_state)
    {
        if (original_state.size() != changed_state.size())
            return true;

        for (int index_line = 0; index_line < original_state.size(); ++index_line)
        {
            int original_state_words_count = original_state[index_line].get_container().size();
            int changed_state_words_count = changed_state[index_line].get_container().size();

            if (original_state_words_count != changed_state_words_count)
                return true;

            for (int index_word = 0; index_word < original_state_words_count; ++index_word)
            {
                if (original_state[index_line][index_word] != changed_state[index_line][index_word])
                    return true;
            }
        }
        return false;
    }
};