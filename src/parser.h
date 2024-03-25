#ifndef PARSER_H
#define PARSER_H

#include "block.h"
#include "pattern.h"
#include "common.h"

#include <string>
#include <filesystem>
#include <optional>
#include <variant>
#include <fstream>
#include <unordered_map>

struct presets_settings
{
    std::filesystem::path presets_file_path;
    std::string delimiter;
    size_t delimiter_length;
};

struct parser_settings
{
    std::filesystem::path pattern_file_path;
    struct presets_settings presets_settings;
};

class parser
{
public:
    explicit parser(const parser_settings& parser_settings);

    void add_character_set(const std::string& key, const std::string& value);
    std::optional<std::string> try_getting_character_set(const std::string& key) const;
    void print_character_sets() const;

    std::variant<pattern, error_message> try_parsing_file();
    
private:
    parser_settings m_settings;
    std::unordered_map<std::string, std::string> m_character_sets;

private:
    void load_character_sets();
    std::optional<error_message> try_parsing_line(pattern &current_pattern, const std::string& line);
};

#endif