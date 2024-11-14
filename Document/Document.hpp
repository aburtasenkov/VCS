#include <list>
#include "Line.hpp"

namespace DocumentClass
{
    class Document{
    public:
        // User - Interface
        Document();
        Document(std::istream& is);

        Document& operator=(Document&& other);

        // Developer - Interface
        std::list<LineClass::Line>& get_container() {
            return lines;
        }
    private: 
        std::list<LineClass::Line> lines;

    };
}