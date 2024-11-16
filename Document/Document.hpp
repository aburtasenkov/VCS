#include <list>
#include <filesystem>
#include <fstream>
#include "Line.hpp"

namespace DocumentClass
{
    class Document{
    public:
        // User - Interface
        Document();
        Document(std::istream& is);
        Document(const std::filesystem::path& path_to_input_file);

        Document& operator=(Document&& other);

        LineClass::Line& operator[](int index);

        int size() const
        {
            return lines.size();
        }

        // Developer - Interface
        std::list<LineClass::Line>& get_container() {
            return lines;
        }
    private: 
        std::list<LineClass::Line> lines;
    };
}
