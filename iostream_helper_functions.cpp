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
    while(is.get(ch))
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
// concantenate input_string until sequence of 2 chars is reached
// return true if seq was reached otherwise false
{
    char ch;
    while(is.get(ch))
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

bool contains_data(std::istream& is)
// return true if is has any left data
{
    return is.peek();
}

std::string ignore_char(const std::string& str, char to_be_ignored)
{
    std::string char_free;
    for (char ch : str)
    {
        if (ch != to_be_ignored)
            char_free += ch;
    }
    return char_free;
}

void get_indexed_line(std::istream& is, std::string& str, int index)
{
    while(index--)
        std::getline(is, str);
}

void get_last_line(std::istream& is, std::string& str)
{
    while(std::getline(is, str));
}
