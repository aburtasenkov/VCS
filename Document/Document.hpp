#include <list>
#include <filesystem>
#include <fstream>
#include "Line.hpp"

namespace DocumentClass
{
    class Document{
    public:
        // STL - Interface
        typedef std::list<LineClass::Line>::iterator iterator;

        iterator begin()
        {
            return lines.begin();
        }

        iterator end()
        {
            return lines.end();
        }

        // User - Interface
        Document();
        Document(std::istream& is);
        Document(const std::filesystem::path& path_to_input_file);
        
        LineClass::Line& operator[](int index);

        int size() const
        {
            return lines.size();
        }
    private: 
        std::list<LineClass::Line> lines;
    };
}
