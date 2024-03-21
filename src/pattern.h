#ifndef PATTERN_H
#define PATTERN_H

#include "block.h"
#include <string>
#include <vector>
#include <unordered_map>

class pattern
{
public:
    pattern(const std::string &name);

    void add_metadata(const std::string &key, const std::string &value);
    void add_block();

    void print_metadata() const;
    void generate_all_combinations() const;

private:
    std::unordered_map<std::string, std::string> m_metadata;
    std::vector<block> m_blocks;
};

#endif