#ifndef SEQUENCE_PARSER_H
#define SEQUENCE_PARSER_H

#include "line-parser.h"
#include <optional>
#include <variant>

/* 1-3;letter+digit-[1234]
    *          *
    |          |
    |          + character set  
    + surface
*/

enum class sequence_state
{
    surface,
    character_set
};

class sequence_parser : public line_parser
{
public:
    explicit sequence_parser(parser& parser);
    virtual ~sequence_parser() = default;
    
    std::optional<error_message> parse_line(pattern &current_pattern, const std::string& line) override;

private:
    sequence_state m_state;

    // Version 1
    std::optional<error_message> parse_line_v1(pattern &current_pattern, const std::string& line);
    std::variant<int, error_message> parse_surface_v1(pattern &current_pattern, const std::string& surface);
    std::optional<error_message> parse_character_set_v1(pattern &current_pattern, const std::string& character_set, int created_blocks);
};

#endif