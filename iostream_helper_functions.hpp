#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

bool next_char_is(std::istream& is, const char prediction)
// return true if next char in stream is prediction
{
    char ch = is.peek();
    return (ch == prediction);
}

bool is_curly_bracket(char ch)

{
    return (ch == '{' || ch == '}');
}

bool input_until_char(std::istream& is, std::string& input_string, const char delim)
// concantenate input_string until delim character is reached
// return true if delim was reached otherwise false
{
    char ch;
    while(is >> ch)
    {
        if (ch == delim)
        {
            is.putback(ch);
            break;
        }
        input_string += ch;
    }
    return true;
}
