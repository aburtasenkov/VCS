#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

namespace LineClass{
    class Line{
        public:
            // User-Interface

            Line();

            Line(const std::string& line);

            Line(const std::vector<std::string>& const_ref);

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