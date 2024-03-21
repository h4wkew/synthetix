#include "sequence-parser.h"

#include <iostream>

sequence_parser::sequence_parser()
    : m_state(sequence_state::surface)
{}

std::optional<error_message> sequence_parser::parse_line(pattern &current_pattern, const std::string& line)
{
    // for (const char c : line)
    // {
    //     switch (state)
    //     {
    //         case sequence_state::surface:
    //             if (c == ';')
    //             {
    //                 state = sequence_state::presets;
    //             }
    //             break;
    //         case sequence_state::presets:
    //             if (c == ';')
    //             {
    //                 state = sequence_state::constraints;
    //             }
    //             break;
    //         case sequence_state::constraints:
    //             break;
    //     }
    // }

    std::cout << "Parsing sequence line: " << line << std::endl;
    return std::nullopt;
}