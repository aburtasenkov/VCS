#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace LineClass{
    class Line{
        public:
            // User-Interface

            Line();

            Line(const std::string& line);

            Line(const std::vector<std::string>& const_ref);

            bool operator==(Line& other)
            {
                return std::equal(words.begin(), words.end(), other.get_container().begin());
            }

            bool operator!=(Line& other)
            {
                return !(*this == other);
            }

            std::string& operator[](int i);
            const std::string& operator[](int i) const;

            void push_back(const std::string& string);
            
            // Developer-Interface

            std::vector<std::string>& get_container(); 
        private:
            std::vector<std::string> words;
    };

    std::ostream& operator<<(std::ostream& os, Line ll);
}