#include "comment-parser.h"

#include <iostream>

comment_parser::comment_parser(parser& parser)
    : line_parser(parser)
{}

std::optional<error_message> comment_parser::parse_line(pattern &current_pattern, const std::string& line)
{
    // Ignore comments
    return std::nullopt;
}