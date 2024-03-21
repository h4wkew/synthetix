#include "parser.h"
#include <iostream>

parser::parser(const parser_settings& parser_settings)
    : m_settings(parser_settings)
{
    auto error_load_presets = load_presets();
    if (error_load_presets)
    {
        std::cerr << "Unable to load presets. (" << error_load_presets.value() << ")" << std::endl;
    }
}

std::variant<pattern, error_message> parser::try_parse_file()
{
    if (m_settings.pattern_file_path.empty())
    {
        return {"Pattern file path is empty."};
    }

    std::ifstream pattern_file(m_settings.pattern_file_path);
    if (!pattern_file.is_open())
    {
        return {"Unable to open the pattern file."};
    }

    // Create a pattern object
    std::string pattern_name = m_settings.pattern_file_path.filename().string();
    pattern current_pattern(pattern_name);

    // Parse the file line by line
    std::string line;
    while (std::getline(pattern_file, line))
    {
        auto error_parse_line = parse_line(current_pattern, line);
        if (error_parse_line)
        {
            return error_parse_line.value();
        }
    }

    current_pattern.print_metadata();

    return current_pattern;
}

std::optional<error_message> parser::load_presets()
{
    if (m_settings.presets_settings.presets_file_path.empty())
    {
        return {"Presets file path is empty."};
    }

    std::ifstream presets_file(m_settings.presets_settings.presets_file_path);
    if (!presets_file.is_open())
    {
        return {"Unable to open the presets file."};
    }

    std::string line;
    while (std::getline(presets_file, line))
    {
        auto delimiter_position = line.find(m_settings.presets_settings.delimiter);
        if (delimiter_position == std::string::npos)
        {
            return {"Invalid preset format."};
        }

        auto key = line.substr(0, delimiter_position);
        auto value = line.substr(delimiter_position + m_settings.presets_settings.delimiter_length);

        m_presets[key] = value;
    }

    return std::nullopt;
}

std::optional<error_message> parser::parse_line(pattern &current_pattern, const std::string& line)
{
    if (line.empty()) return std::nullopt;

    /* State machine
        - Comment
        - Metadata
        - Sequence (one or more blocks)
    */

    switch (line[0])
    {
        case '#':
            parse_comment_line(current_pattern, line);
            break;
        case '%':
            parse_metadata_line(current_pattern, line);
            break;
        default:
            parse_sequence_line(current_pattern, line);
            break;
    }

    return std::nullopt;
}

std::optional<error_message> parser::parse_comment_line(pattern &current_pattern, const std::string& line)
{
    // Log debug message
    return std::nullopt;
}

std::optional<error_message> parser::parse_metadata_line(pattern &current_pattern, const std::string& line)
{
    std::string key = line.substr(1, line.find(' ') - 1);
    std::string value = line.substr(line.find(' ') + 1);

    current_pattern.add_metadata(key, value);
    // Log debug message

    return std::nullopt;
}

std::optional<error_message> parser::parse_sequence_line(pattern &current_pattern, const std::string& line)
{
    // state machine

    std::cout << "Sequence: " << line << std::endl;
    return std::nullopt;
}