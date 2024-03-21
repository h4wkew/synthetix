#include "parser.h"
#include "line-parser.h"
#include "comment-parser.h"
#include "metadata-parser.h"
#include "sequence-parser.h"

#include <iostream>

parser::parser(const parser_settings& parser_settings)
    : m_settings(parser_settings)
{
    auto error_load_presets = load_presets();
    if (error_load_presets)
    {
        std::cerr << "Unable to load presets. (" << error_load_presets.value() << ")" << std::endl;
    }

    /* DEBUG */ print_presets();
}

void parser::print_presets() const
{
    if (m_presets.empty()) return;

    std::cout << "Presets:" << std::endl;
    for (const auto& [key, value] : m_presets)
    {
        std::cout << " * " << key << ": " << value << std::endl;
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

    std::unique_ptr<line_parser> line_parser;
    char first_char = line[0];

    switch (first_char)
    {
        case '#':
            line_parser = std::make_unique<comment_parser>();
            break;
        case '%':
            line_parser = std::make_unique<metadata_parser>();
            break;
        default:
            line_parser = std::make_unique<sequence_parser>();
            break;
    }

    if (!line_parser)
    {
        return {"Empty line parser."};
    }

    line_parser->parse_line(current_pattern, line);

    return std::nullopt;
}