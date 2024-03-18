#include "parser.h"
#include <iostream>

parser::parser(const parser_settings& parser_settings)
    : m_settings(parser_settings)
{
    // open the pattern file
    // open the presets file
}

std::variant<pattern, error_message> parser::try_parse_file()
{
    return {"Error parsing pattern file."};
}

std::variant<std::ifstream, error_message> parser::try_open_pattern_file()
{
    return {"Error opening pattern file."};
}

std::variant<std::ifstream, error_message> parser::try_open_presets_file()
{
    return {"Error opening presets file."};
}

std::vector<block> parser::try_parse_line(const std::string& line) const
{
    return {};
}