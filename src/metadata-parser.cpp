#include "metadata-parser.h"

#include <iostream>

std::optional<error_message> metadata_parser::parse_line(pattern &current_pattern, const std::string& line)
{
    std::cout << "Parsing metadata line: " << line << std::endl;
    
    std::string key = line.substr(1, line.find(' ') - 1);
    std::string value = line.substr(line.find(' ') + 1);

    current_pattern.add_metadata(key, value);
    
    return std::nullopt;
}