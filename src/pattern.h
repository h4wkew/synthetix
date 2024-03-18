#ifndef PATTERN_H
#define PATTERN_H

#include "block.h"
#include <string>
#include <vector>

class pattern
{
public:
    pattern(const std::string &name);

    void add_block();
    void generate_all_combinations() const;

private:
    std::string m_name;
    std::vector<block> m_blocks;
};

#endif