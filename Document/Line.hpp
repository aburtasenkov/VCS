#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace LineClass{
    class Line{
        public:
            // STL Interface
            typedef std::vector<std::string>::iterator iterator;

            iterator begin()
            {
                return words.begin();
            }

            iterator end()
            {
                return words.end();
            }

            // User-Interface

            Line();

            Line(const std::string& line);

            Line(const std::vector<std::string>& const_ref);

            bool operator==(Line& other)
            {
                return std::equal(words.begin(), words.end(), other.begin());
            }

            bool operator!=(Line& other)
            {
                return !(*this == other);
            }

            std::string& operator[](int i);
            const std::string& operator[](int i) const;
        private:
            std::vector<std::string> words;
    };

    std::ostream& operator<<(std::ostream& os, Line ll);
}