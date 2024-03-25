#ifndef CUSTOM_SET_PARSER_H
#define CUSTOM_SET_PARSER_H

#include "line-parser.h"

class custom_set_parser : public line_parser
{
public:
    explicit custom_set_parser(parser& parser);
    virtual ~custom_set_parser() = default;

    std::optional<error_message> parse_line(pattern &current_pattern, const std::string& line) override;
};

#endif