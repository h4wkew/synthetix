#ifndef PATTERN_H
#define PATTERN_H

#include "block.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

class pattern
{
public:
    pattern(const std::string &name);

    void add_empty_blocks(int count);
    std::vector<std::reference_wrapper<block>> get_last_n_blocks(int count);
    void print_blocks() const;

    void add_metadata(const std::string &key, const std::string &value);
    std::optional<std::string> get_metadata(const std::string &key) const;
    void print_metadata() const;

    void generate_all_combinations(std::ofstream& output) const;

private:
    std::unordered_map<std::string, std::string> m_metadata;
    std::vector<block> m_blocks;
};

#endif