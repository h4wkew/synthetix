#ifndef METADATA_PARSER_H
#define METADATA_PARSER_H

#include "line-parser.h"

class metadata_parser : public line_parser
{
public:
    explicit metadata_parser(parser& parser);
    virtual ~metadata_parser() = default;

    std::optional<error_message> parse_line(pattern &current_pattern, const std::string& line) override;
};

#endif