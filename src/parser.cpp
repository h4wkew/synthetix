#include "parser.h"
#include "line-parser.h"
#include "comment-parser.h"
#include "metadata-parser.h"
#include "custom-set-parser.h"
#include "sequence-parser.h"

#include <iostream>

parser::parser(const parser_settings& parser_settings)
    : m_settings(parser_settings)
{
    load_character_sets();
}

void parser::add_character_set(const std::string& key, const std::string& value)
{
    m_character_sets.insert({key, value});
}

std::optional<std::string> parser::try_getting_character_set(const std::string& key) const
{
    if (auto it = m_character_sets.find(key); it != m_character_sets.end())
    {
        return it->second;
    }

    return std::nullopt;
}

void parser::print_character_sets() const
{
    if (m_character_sets.empty()) return;

    std::cout << "Presets:" << std::endl;
    for (const auto& [key, value] : m_character_sets)
    {
        std::cout << " * " << key << ": " << value << std::endl;
    }
}

std::variant<pattern, error_message> parser::try_parsing_file()
{
    if (m_settings.pattern_file_path.empty())
    {
        return error_message("Pattern file path is empty.");
    }

    std::ifstream pattern_file(m_settings.pattern_file_path);
    if (!pattern_file.is_open())
    {
        return error_message("Unable to open the pattern file.");
    }

    // Create a pattern object
    std::string filename = m_settings.pattern_file_path.filename().string();
    std::string pattern_name = filename.substr(0, filename.find_last_of('.'));
    pattern current_pattern(pattern_name);

    // Parse the file line by line
    std::string line;
    while (std::getline(pattern_file, line))
    {
        auto error_parsing_line = try_parsing_line(current_pattern, line);
        if (error_parsing_line)
        {
            return error_parsing_line.value();
        }
    }

    return current_pattern;
}

void parser::load_character_sets()
{
    m_character_sets = {
        {"all", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"},
        {"letter", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"},
        {"lower", "abcdefghijklmnopqrstuvwxyz"},
        {"upper", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
        {"digit", "0123456789"},
        {"special", "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"}
    };
}

std::optional<error_message> parser::try_parsing_line(pattern &current_pattern, const std::string& line)
{
    if (line.empty()) return std::nullopt;

    std::unique_ptr<line_parser> line_parser;
    char first_char = line[0];

    switch (first_char)
    {
        case '#':
            line_parser = std::make_unique<comment_parser>(*this);
            break;
        case '%':
            line_parser = std::make_unique<metadata_parser>(*this);
            break;
        case '~':
            line_parser = std::make_unique<custom_set_parser>(*this);
            break;
        default:
            line_parser = std::make_unique<sequence_parser>(*this);
            break;
    }

    if (!line_parser)
    {
        return error_message("Empty line parser.");
    }

    return line_parser->parse_line(current_pattern, line);
}