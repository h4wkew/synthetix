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

    void print_presets() const;
    std::variant<pattern, error_message> try_parse_file();
    
private:
    parser_settings m_settings;
    std::unordered_map<std::string, std::string> m_presets;

private:
    std::optional<error_message> load_presets();
    std::optional<error_message> parse_line(pattern &current_pattern, const std::string& line);
};

#endif