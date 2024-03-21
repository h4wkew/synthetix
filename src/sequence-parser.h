#ifndef SEQUENCE_PARSER_H
#define SEQUENCE_PARSER_H

#include "line-parser.h"

/* 1-3;letter+digit;![1234]
    *        *          *
    |        |          + constraints
    |        + presets  
    + surface
*/

enum class sequence_state
{
    surface,
    presets,
    constraints,
};

class sequence_parser : public line_parser
{
public:
    sequence_parser();
    virtual ~sequence_parser() = default;
    
    std::optional<error_message> parse_line(pattern &current_pattern, const std::string& line) override;

private:
    sequence_state m_state;
};

#endif