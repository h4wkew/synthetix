#ifndef LINE_PARSER_H
#define LINE_PARSER_H

#include "common.h"
#include "pattern.h"
#include <string>
#include <optional>

class line_parser
{
public:
    virtual ~line_parser() = default;
    virtual std::optional<error_message> parse_line(pattern &current_pattern, const std::string& line) = 0;
};

#endif