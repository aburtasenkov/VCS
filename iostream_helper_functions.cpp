#include "iostream_helper_functions.hpp"

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

bool input_until_pair(std::istream& is, std::string& input_string, const std::pair<char, char> seq)
{
    char ch;
    while(is >> ch)
    {
        if (ch == seq.first && is.peek() == seq.second)
        {
            is.putback(ch);
            break;
        }
        input_string += ch;
    }
    return true;
}