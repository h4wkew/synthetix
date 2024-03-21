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

struct parser_settings
{
    std::filesystem::path pattern_file_path;
    std::filesystem::path presets_file_path;
};

class parser
{
public:
    explicit parser(const parser_settings& parser_settings);

    std::variant<pattern, error_message> try_parse_file();
    
private:
    parser_settings m_settings;
    std::ifstream m_pattern_file;

private:
    std::variant<std::ifstream, error_message> try_open_pattern_file();
    std::variant<std::ifstream, error_message> try_open_presets_file();

    std::vector<block> try_parse_line(const std::string& line) const;
};

#endif