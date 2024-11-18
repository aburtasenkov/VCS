#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace Line_Namespace{
    class Line{
        public:
            // STL - Interface
            typedef std::vector<std::string>::iterator iterator;
            typedef std::vector<std::string>::const_iterator const_iterator;

            const_iterator begin() const;
            const_iterator end() const;
            iterator begin();
            iterator end();
            
            // User-Interface
            Line();
            Line(const std::string& line);
            Line(const std::vector<std::string>& const_ref);

            bool operator==(const Line& other) const;
            bool operator!=(const Line& other) const;

            std::string& operator[](int index);
            const std::string& operator[](int index) const;
            int size() const;
        private:
            std::vector<std::string> words;
    };

    std::ostream& operator<<(std::ostream& os, const Line& line);
}