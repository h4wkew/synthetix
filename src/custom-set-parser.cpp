#include "custom-set-parser.h"

#include <iostream>

/* Examples :
 
 ~even 02468
 ~odd 13579

*/

custom_set_parser::custom_set_parser(parser& parser)
    : line_parser(parser)
{}

std::optional<error_message> custom_set_parser::parse_line(pattern &current_pattern, const std::string& line)
{
    std::string key = line.substr(1, line.find(' ') - 1);
    std::string value = line.substr(line.find(' ') + 1);

    for (const char c : key)
    {
        if (!std::isalpha(c) && c != '-' && c != '_')
        {
            return error_message("Character set name could only contain alphabets and '-' or '_'."); 
        }
    }

    m_parser.add_character_set(key, value);

    return std::nullopt;
}