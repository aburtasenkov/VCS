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

            iterator begin();
            iterator end();
            
            // User-Interface
            Line();
            Line(const std::string& line);
            Line(const std::vector<std::string>& const_ref);

            bool operator==(Line& other);
            bool operator!=(Line& other);

            std::string& operator[](int i);
            const std::string& operator[](int i) const;
            int size();
        private:
            std::vector<std::string> words;
    };

    std::ostream& operator<<(std::ostream& os, Line ll);
}