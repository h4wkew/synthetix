#include "sequence-parser.h"

#include <iostream>

sequence_parser::sequence_parser()
    : m_state(sequence_state::surface)
{}

std::optional<error_message> sequence_parser::parse_line(pattern &current_pattern, const std::string& line)
{
    std::cout << "Parsing sequence line: " << line << std::endl;

    auto version = current_pattern.get_metadata("version").value_or("1.0");
    if (version == "1.0")
    {
        return parse_line_v1(current_pattern, line);
    }

    return error_message("Unknown pattern file version");
}

std::optional<error_message> sequence_parser::parse_line_v1(pattern &current_pattern, const std::string& line)
{
    size_t delimiter_position = line.find(';');
    if (delimiter_position == std::string::npos)
    {
        return error_message("No delimiter found in sequence line");
    }

    // Create empty block(s)
    std::string surface = line.substr(0, delimiter_position);
    auto surface_result = parse_surface_v1(current_pattern, surface);
    if (std::holds_alternative<error_message>(surface_result))
    {
        return std::get<error_message>(surface_result);
    }

    int created_blocks = std::get<int>(surface_result);

    // Fill the block(s) with character sets
    std::string character_sets = line.substr(delimiter_position + 1);
    if (auto error = parse_character_set_v1(current_pattern, character_sets, created_blocks); error.has_value())
    {
        return error;
    }

    return std::nullopt;
}

std::variant<int, error_message> sequence_parser::parse_surface_v1(pattern &current_pattern, const std::string& surface)
{
    int created_blocks = 0;

    try
    {
        size_t dash_position = surface.find('-');
        if (dash_position == std::string::npos)
        {
            created_blocks = std::stoi(surface);
            current_pattern.add_empty_blocks(created_blocks);
        }
        else
        {
            int min = std::stoi(surface.substr(0, dash_position));
            int max = std::stoi(surface.substr(dash_position + 1));

            if (min > max)
            {
                return error_message("Invalid range surface");
            }

            // TODO: Implement range surface
            return error_message("Range surface not implemented yet");
        }
        
    }
    catch (const std::invalid_argument &)
    {
        return error_message("Invalid surface format");
    }

    return created_blocks;
}

std::optional<error_message> sequence_parser::parse_character_set_v1(pattern &current_pattern, const std::string& character_set, int created_blocks)
{
    std::cout << "Character set string: " << character_set << std::endl;
    std::cout << "Number of blocks created: " << created_blocks << std::endl;

    auto latest_blocks = current_pattern.get_last_n_blocks(created_blocks);
    if (latest_blocks.empty())
    {
        return error_message("No blocks to fill with character set");
    }

    for (auto& block : latest_blocks)
    {
        block.get().add_chars("abc");
    }

    current_pattern.print_blocks();
    return std::nullopt;
}