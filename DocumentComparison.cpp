#include "DocumentComparison.hpp"

bool is_document_changed(DocumentClass::Document& original_state, DocumentClass::Document& changed_state)
// return true if a document was changed
// return false if the document stayed the same
{
    // same amount of lines?
    if (original_state.size() != changed_state.size())
        return true;

    // iterate through each line
    for (int index_line = 0; index_line < original_state.size(); ++index_line)
    {
        int original_state_line_words_count = original_state[index_line].get_container().size();
        int changed_state_line_words_count = changed_state[index_line].get_container().size();

        // same amount of words?
        if (original_state_line_words_count != changed_state_line_words_count)
            return true;

        //  iterate and compare each word together
        for (int index_word = 0; index_word < original_state_line_words_count; ++index_word)
        {
            if (original_state[index_line][index_word] != changed_state[index_line][index_word])
                return true;
        }
    }
    return false;
