#ifndef COMMENT_PARSER_H
#define COMMENT_PARSER_H

#include "line-parser.h"

class comment_parser : public line_parser
{
public:
    virtual ~comment_parser() = default;
    std::optional<error_message> parse_line(pattern &current_pattern, const std::string& line) override;
};

#endif