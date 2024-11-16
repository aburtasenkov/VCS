#include "Document/Document.hpp"

namespace Comparison
{
    class DocumentComparison
    {
        private:
            std::vector<std::pair<LineClass::Line, int>> added_lines;    // stores lines that were added at index int
            std::vector<int> removed_lines; // stores indexes of lines that were removed
    };
};