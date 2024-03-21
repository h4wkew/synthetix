#include "comment-parser.h"

#include <iostream>

std::optional<error_message> comment_parser::parse_line(pattern &current_pattern, const std::string& line)
{
    std::cout << "Parsing comment line: " << line << std::endl;
    return std::nullopt;
}