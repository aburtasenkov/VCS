#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

bool next_char_is(std::istream& is, const char prediction);
bool is_curly_bracket(char ch);
bool input_until_char(std::istream& is, std::string& input_string, const char delim);
bool input_until_pair(std::istream& is, std::string& input_string, const std::pair<char, char> seq);
bool contains_data(std::istream& is);
std::string ignore_char(const std::string& str, char to_be_ignored);
void get_indexed_line(std::istream& is, std::string& str, int index);
void get_last_line(std::istream& is, std::string& str);
std::string ignore_first_n_chars(const std::string& str, int count);